#include <cstdio>
#include <iostream>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

#include "NDISender.h"
#include "NDIReceiver.h"

PYBIND11_MODULE(simplendi, m) {
    m.doc() = "Python binding of NDI";

    py::class_<NDISender>(m, "NDISender")
        .def(py::init<const std::string&>())
        .def("send", (void (NDISender::*)(py::array_t<unsigned char>)) &NDISender::send)
        .def("setName", (void (NDISender::*)(std::string)) &NDISender::setName);

    py::class_<NDIReceiver>(m, "NDIReceiver")
        .def(py::init<>())
        .def("getSourceList", (std::vector<std::string> (NDIReceiver::*)()) &NDIReceiver::getSourceList)
        .def("setSource", (bool (NDIReceiver::*)(const std::string)) &NDIReceiver::setSource)
        .def("getCurrentFrame", (py::array_t<unsigned char>(NDIReceiver::*)()) &NDIReceiver::getCurrentFrame)
        .def("addHandler", (void (NDIReceiver::*)(const std::string& name, const std::function<void(py::array_t<unsigned char>)> &f)) &NDIReceiver::addHandler)
        .def("removeHandler", (void (NDIReceiver::*)(const std::string& name)) &NDIReceiver::removeHandler);
}