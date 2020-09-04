#include "NDIReceiver.h"

NDIReceiver::NDIReceiver() {
    if (!NDIlib_initialize()) return;

    NDIlib_find_create_t NDI_find_create_desc;
    ndi_find = NDIlib_find_create_v2(&NDI_find_create_desc);
    if (!ndi_find) return;
}

NDIReceiver::~NDIReceiver() {
    NDIlib_find_destroy(ndi_find);
}

void NDIReceiver::updateSourceList() {
    uint32_t no_sources = 0;
    const NDIlib_source_t* data;
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

    for (auto& s : source_list) {
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
    } catch (std::out_of_range& oor) {
        std::cerr << "NDIReceive:: source is not specified or wrong" << std::endl;
        return false;
    }

    recv_desc.p_ndi_recv_name = "Example NDI Receiver";

    ndi_receive = NDIlib_recv_create_v3(&recv_desc);

    if (!ndi_receive) return false;


    NDIlib_tally_t tally_state;
    tally_state.on_program = true;
    tally_state.on_preview = true;
    NDIlib_recv_set_tally(ndi_receive, &tally_state);

    return true;
}

bool NDIReceiver::setSource(const std::string& ndiName) {
    for (int i = 0; i < source_list.size(); ++i) {
        if (source_list[i].p_ndi_name == ndiName) {
            sourceId = i;
            return createNDIReceive();
        }
    }

    return false;
}

void NDIReceiver::addHandler() {

}

py::array_t<unsigned char> NDIReceiver::getCurrentFrame() const {
    return py::array_t<unsigned char>();
}

