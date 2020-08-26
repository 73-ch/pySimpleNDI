#include <cstdio>
#include <iostream>

#include "NDISender.h"

NDISender::NDISender() {
    if (!NDIlib_initialize()) return;

    ndi_send = NDIlib_send_create();
    if (!ndi_send) return;

    ndi_frame.p_data = (uint8_t *) malloc(sizeof(uint8_t) * 256 * 256 * 4);
    ndi_frame.FourCC = NDIlib_FourCC_type_BGRX;
}

NDISender::~NDISender() {
    free(ndi_frame.p_data);

    NDIlib_send_destroy(ndi_send);

    NDIlib_destroy();
}

bool NDISender::checkShape(const std::vector<ssize_t> &shape) {
    if (ndi_frame.xres != shape[0] || ndi_frame.yres != shape[1]) {
        changeResolution(shape[1], shape[0]);
    }

    if (shape[2] == 3) {
        ndi_frame.FourCC = NDIlib_FourCC_type_BGRX;
    } else if (shape[2] == 4) {
        ndi_frame.FourCC = NDIlib_FourCC_type_BGRA;
    } else {
        std::cerr << "NDISender:: source shape[2] must be 3 or 4." << std::endl;
        return false;
    }

    return true;
}

void NDISender::copyFrame(const py::array_t<unsigned char> &frame) const {

    if (ndi_frame.FourCC == NDIlib_FourCC_type_BGRA) {
        memcpy((unsigned char *) ndi_frame.p_data, frame.data(), frame.size());
    } else if (ndi_frame.FourCC == NDIlib_FourCC_type_BGRX) {
        for (int i = 0; i < ndi_frame.yres; ++i) {
            for (int j = 0; j < ndi_frame.xres; ++j) {
                ndi_frame.p_data[(i * ndi_frame.xres + j) * 4] = (uint8_t) *frame.data(i, j, 0);
                ndi_frame.p_data[(i * ndi_frame.xres + j) * 4 + 1] = (uint8_t) *frame.data(i, j, 1);
                ndi_frame.p_data[(i * ndi_frame.xres + j) * 4 + 2] = (uint8_t) *frame.data(i, j, 2);
                ndi_frame.p_data[(i * ndi_frame.xres + j) * 4 + 3] = 255;
            }
        }
    }
}

void NDISender::changeResolution(const int xres, const int yres) {
    uint8_t *tmp;

    ndi_frame.xres = xres;
    ndi_frame.yres = yres;
    buffer_size = xres * yres * 4;

    if ((tmp = (uint8_t *) realloc(ndi_frame.p_data, buffer_size)) != nullptr) {
        ndi_frame.p_data = tmp;
    } else {
        std::cerr << "allocation error" << std::endl;
    }
}

void NDISender::send(const py::array_t<unsigned char> &frame) {
    const auto info = frame.request();

    if (!checkShape(info.shape)) return;

    copyFrame(frame);

    NDIlib_send_send_video_v2(ndi_send, &ndi_frame);
}