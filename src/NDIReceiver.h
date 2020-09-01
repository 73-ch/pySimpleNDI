#ifndef SIMPLENDI_NDIRECEIVER_H
#define SIMPLENDI_NDIRECEIVER_H

#include <cstddef>

#include <Processing.NDI.Lib.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

class NDIReceiver {
    std::vector<NDIlib_source_t> sources;

    void updateSources();

public:
    NDIlib_find_instance_t ndi_find;

    NDIReceiver();
    ~NDIReceiver();

    std::vector<std::string> getSourceList();
    void setSourceId(unsigned int id);
    void addHandler();
    py::array_t<unsigned char> getCurrentFrame() const;

};


#endif //SIMPLENDI_NDIRECEIVER_H
