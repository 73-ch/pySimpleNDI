#include "NDIReceiver.h"

NDIReceiver::NDIReceiver() {
    if (!NDIlib_initialize()) return;

    NDIlib_find_create_t NDI_find_create_desc;
    ndi_find = NDIlib_find_create_v2(&NDI_find_create_desc);
    if (!ndi_find) return;
}

void NDIReceiver::updateSources() {
    uint32_t no_sources = 0;
    const NDIlib_source_t* data;
    while (!no_sources) {
        NDIlib_find_wait_for_sources(ndi_find, 1000);
        data = NDIlib_find_get_current_sources(ndi_find, &no_sources);
    }

    sources.resize(no_sources);

    std::copy(data, data + no_sources, sources.begin());
}

std::vector<std::string> NDIReceiver::getSourceList() {
    updateSources();

    std::vector<std::string> source_names;

    for (auto& s : sources) {
        source_names.emplace_back(s.p_ndi_name);
    }

    return source_names;
}

NDIReceiver::~NDIReceiver() {
    NDIlib_find_destroy(ndi_find);
}

void NDIReceiver::setSourceId(const unsigned int id) {

}

void NDIReceiver::addHandler() {

}

py::array_t<unsigned char> NDIReceiver::getCurrentFrame() const {
    return py::array_t<unsigned char>();
}

