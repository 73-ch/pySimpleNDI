#ifndef NDIPYTHON_NDISENDER_H
#define NDIPYTHON_NDISENDER_H
#include <Processing.NDI.Lib.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

using ssize_t = Py_ssize_t;

namespace py = pybind11;

class NDISender {
    int buffer_size;
    bool isNDISendInitialized = false;

    bool checkShape(const std::vector <ssize_t> &shape);
    void copyFrame(const py::array_t<unsigned char> &frame) const;
    void changeResolution(int xres, int yres);
    void initNDISend();

public:
    NDIlib_send_instance_t ndi_send;
    NDIlib_video_frame_v2_t ndi_frame;
    NDIlib_send_create_t ndi_desc;

    NDISender(const std::string& name = "pysimplendi");
    ~NDISender();

    void setName(const std::string& name = "pysimplendi");
    void send(const py::array_t<unsigned char> &frame);
};

#endif //NDIPYTHON_NDISENDER_H
