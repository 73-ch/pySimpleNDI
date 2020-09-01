#include <cstdio>
#include <iostream>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

#include "NDISender.h"

PYBIND11_MODULE(simplendi, m) {
    m.doc() = "Python binding of NDI";

    py::class_<NDISender>(m, "NDISender")
        .def(py::init<const std::string&>())
        .def("send", (void (NDISender::*)(py::array_t<unsigned char>)) &NDISender::send)
        .def("setName", (void (NDISender::*)(std::string)) &NDISender::setName);
}