#ifndef NDIPYTHON_NDISENDER_H
#define NDIPYTHON_NDISENDER_H
#include <Processing.NDI.Lib.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

class NDISender {
    int buffer_size;

    bool checkShape(const std::vector <ssize_t> &shape);
    void copyFrame(const py::array_t<unsigned char> &frame) const;
    void changeResolution(const int xres, const int yres);

public:
    NDIlib_send_instance_t ndi_send;
    NDIlib_video_frame_v2_t ndi_frame;

    NDISender();
    ~NDISender();
    void send(const py::array_t<unsigned char> &frame);
};

#endif //NDIPYTHON_NDISENDER_H
