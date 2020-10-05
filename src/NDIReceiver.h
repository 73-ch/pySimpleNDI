#ifndef SIMPLENDI_NDIRECEIVER_H
#define SIMPLENDI_NDIRECEIVER_H

#include <cstddef>
#include <iostream>
#include <future>
#include <map>

#include <Processing.NDI.Lib.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include "Converter.h"

namespace py = pybind11;

class NDIReceiver {
    std::vector<NDIlib_source_t> source_list;
    int sourceId = -1;
    std::thread receiveThread;
    std::mutex mutex;

    py::array_t<unsigned char> result_array;
    py::array_t<unsigned char> tmp_result_array;

    bool receiving = false;

    void updateSourceList();
    bool createNDIReceive();
    void startReceive();
    void stopReceive();
    void receive();

public:
    NDIlib_find_instance_t ndi_find;
    NDIlib_recv_instance_t ndi_receive;

    NDIReceiver();
    ~NDIReceiver();

    std::vector<std::string> getSourceList();
    bool setSource(const std::string& ndiName);
    void addHandler();
    py::array_t<unsigned char> getCurrentFrame() const;

    const std::map<NDIlib_FourCC_video_type_e , int> FourCC2NumBytesPerPixel{
        {NDIlib_FourCC_type_BGRX, 3},
        {NDIlib_FourCC_type_BGRA, 4},
        {NDIlib_FourCC_type_UYVY,4}
    };
};


#endif //SIMPLENDI_NDIRECEIVER_H
