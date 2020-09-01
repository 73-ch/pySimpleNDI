#include "NDIReceiver.h"

NDIReceiver::NDIReceiver() {
    if (!NDIlib_initialize()) return;
}

std::vector<std::string> NDIReceiver::getSourceList() const {
    std::vector<std::string> source_names;


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

