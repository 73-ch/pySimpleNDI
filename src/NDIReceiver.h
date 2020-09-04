#ifndef SIMPLENDI_NDIRECEIVER_H
#define SIMPLENDI_NDIRECEIVER_H

#include <cstddef>
#include <iostream>

#include <Processing.NDI.Lib.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

class NDIReceiver {
    std::vector<NDIlib_source_t> source_list;
    int sourceId = -1;

    void updateSourceList();
    bool createNDIReceive();

public:
    NDIlib_find_instance_t ndi_find;
    NDIlib_recv_instance_t ndi_receive;

    NDIReceiver();
    ~NDIReceiver();

    std::vector<std::string> getSourceList();
    bool setSource(const std::string& ndiName);
    void addHandler();
    py::array_t<unsigned char> getCurrentFrame() const;

};


#endif //SIMPLENDI_NDIRECEIVER_H
