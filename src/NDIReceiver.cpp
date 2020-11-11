#include "NDIReceiver.h"

NDIReceiver::NDIReceiver() {
    if (!NDIlib_initialize()) return;

    NDIlib_find_create_t NDI_find_create_desc;
    ndi_find = NDIlib_find_create_v2(&NDI_find_create_desc);
    if (!ndi_find) return;

    tmp_result_array = py::array_t<unsigned char>({780, 960, 4});
    result_array = py::array_t<unsigned char>({780, 960, 4});
}

NDIReceiver::~NDIReceiver() {
    stopReceive();

    NDIlib_find_destroy(ndi_find);
}

void NDIReceiver::updateSourceList() {
    uint32_t no_sources = 0;
    const NDIlib_source_t *data;
    while (!no_sources) {
        NDIlib_find_wait_for_sources(ndi_find, 1000);
        data = NDIlib_find_get_current_sources(ndi_find, &no_sources);
    }

    source_list.resize(no_sources);

    std::copy(data, data + no_sources, source_list.begin());
}

std::vector<std::string> NDIReceiver::getSourceList() {
    updateSourceList();

    std::vector<std::string> source_names;

    for (auto &s : source_list) {
        source_names.emplace_back(s.p_ndi_name);
    }

    return source_names;
}


bool NDIReceiver::createNDIReceive() {
    if (source_list.empty()) {
        std::cerr << "NDIReceiver:: sources is empty" << std::endl;
        return false;
    }

    NDIlib_recv_create_v3_t recv_desc;

    try {
        recv_desc.source_to_connect_to = source_list[sourceId];
    } catch (std::out_of_range &oor) {
        std::cerr << "NDIReceive:: source is not specified or wrong" << std::endl;
        return false;
    }
    recv_desc.color_format = NDIlib_recv_color_format_BGRX_BGRA;
    recv_desc.p_ndi_recv_name = "Example NDI Receiver";

    ndi_receive = NDIlib_recv_create_v3(&recv_desc);

    if (!ndi_receive) return false;


    NDIlib_tally_t tally_state;
    tally_state.on_program = true;
    tally_state.on_preview = true;
    NDIlib_recv_set_tally(ndi_receive, &tally_state);

    NDIlib_metadata_frame_t enable_hw_accel;
    enable_hw_accel.p_data = const_cast<char *>("<ndi_hwaccel enabled=\"true\"/>");
    NDIlib_recv_send_metadata(ndi_receive, &enable_hw_accel);

    return true;
}

bool NDIReceiver::setSource(const std::string &ndiName) {
    for (int i = 0; i < source_list.size(); ++i) {
        if (source_list[i].p_ndi_name == ndiName) {
            sourceId = i;
            if (createNDIReceive()) {
                startReceive();
                return true;
            } else {
                return false;
            }
        }
    }

    return false;
}

void NDIReceiver::addHandler(const std::string& name, const std::function<void(py::array_t<unsigned char>)>& callback) {
    handlers.insert(std::make_pair(name, callback));
}

void NDIReceiver::removeHandler(const std::string& name) {
    handlers.erase(name);
}

void NDIReceiver::callHandlers() const {
    auto cp_result = result_array;

    for (const auto& x : handlers) {
        x.second(cp_result);
    }
}

py::array_t<unsigned char> NDIReceiver::getCurrentFrame() const {
    auto cp_result = result_array;
    return cp_result;
}

void NDIReceiver::startReceive() {
    if (receiving) return;
    receiving = true;

    receiveThread = std::thread([&] {
        while (receiving) {
            receive();
        }
    });
}

void NDIReceiver::receive() {
    NDIlib_video_frame_v2_t video_frame;
    NDIlib_audio_frame_v2_t audio_frame;
    NDIlib_metadata_frame_t metadata_frame;

    std::lock_guard<std::mutex> lock(mutex);

    switch (NDIlib_recv_capture_v2(ndi_receive, &video_frame, &audio_frame, &metadata_frame, 1000)) {
        // Video data
        case NDIlib_frame_type_video:
            video_frame.p_metadata = nullptr;

//                    std::cout << "four: " << FourCC2NumBytesPerPixel.at(video_frame.FourCC) << std::endl;
//                    std::cout << "(" << video_frame.xres << "," << video_frame.yres << ")" << std::endl;

            tmp_result_array.resize(
                    {video_frame.yres, video_frame.xres, FourCC2NumBytesPerPixel.at(video_frame.FourCC)});

            if (video_frame.FourCC == NDIlib_FourCC_type_UYVY) {
//                std::cout << "UYUV" << std::endl;
                Converter::convertUYVY2RGB((const unsigned char *) video_frame.p_data,
                                           result_array.mutable_data(),
                                           video_frame.xres, video_frame.yres,
                                           video_frame.line_stride_in_bytes);
            } else if (video_frame.FourCC == NDIlib_FourCC_type_BGRA) {
//                std::cout << "RGBA" << std::endl;
                memcpy((unsigned char *) tmp_result_array.mutable_data(), video_frame.p_data, tmp_result_array.size());
            } else if (video_frame.FourCC == NDIlib_FourCC_type_BGRX) {
                // BGRの時のNDI video_frameからnumpy result_arrayへのデータのコピー
//                std::cout << "RGB" << std::endl;
                auto frame = tmp_result_array.mutable_data();
                for (int i = 0; i < video_frame.yres; ++i) {
                    for (int j = 0; j < video_frame.xres; ++j) {
                        *frame++ = video_frame.p_data[(i * video_frame.xres + j) * 4];
                        *frame++ = video_frame.p_data[(i * video_frame.xres + j) * 4 + 1];
                        *frame++ = video_frame.p_data[(i * video_frame.xres + j) * 4 + 2];
                    }
                }
            }

            NDIlib_recv_free_video_v2(ndi_receive, &video_frame);

            std::swap(result_array, tmp_result_array);

            callHandlers();
            break;

            // Audio data
        case NDIlib_frame_type_audio:
            NDIlib_recv_free_audio_v2(ndi_receive, &audio_frame);
            break;

            // Meta data
        case NDIlib_frame_type_metadata:
            NDIlib_recv_free_metadata(ndi_receive, &metadata_frame);
            break;

            // Everything else
        default:
            break;
    }
}

void NDIReceiver::stopReceive() {
    if (receiving) {
        receiving = false;
        receiveThread.join();
    }
}

