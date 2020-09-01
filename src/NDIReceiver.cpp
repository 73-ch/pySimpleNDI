#include "NDIReceiver.h"

NDIReceiver::NDIReceiver() {
    if (!NDIlib_initialize()) return;

    NDIlib_find_create_t NDI_find_create_desc;
    ndi_find = NDIlib_find_create_v2(&NDI_find_create_desc);
    if (!ndi_find) return;
}

std::vector<std::string> NDIReceiver::getSourceList() {
    uint32_t no_sources = 0;
    while (!no_sources){
        NDIlib_find_wait_for_sources(ndi_find, 1000);
        sources = NDIlib_find_get_current_sources(ndi_find, &no_sources);
    }

    std::vector<std::string> source_names;

    for (size_t i = 0; i < no_sources; ++i) {
        source_names.emplace_back(sources[i].p_ndi_name);
    }

    return source_names;
}

NDIReceiver::~NDIReceiver() {

}

void NDIReceiver::setSourceId(const unsigned int id) {

}

void NDIReceiver::addHandler() {

}

py::array_t<unsigned char> NDIReceiver::getCurrentFrame() const {
    return py::array_t<unsigned char>();
}

