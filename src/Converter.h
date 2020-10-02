#ifndef SIMPLENDI_CONVERTER_H
#define SIMPLENDI_CONVERTER_H

class Converter {
public:
    static void
    convertRGB2UYUV(const unsigned char *source, unsigned char *dest, unsigned int width, unsigned int height,
                    unsigned int stride) {

    }


    static void
    convertUYVY2RGB(const unsigned char *source, unsigned char *dest, unsigned int width, unsigned int height,
                    unsigned int stride) {

#define CLAMPRGB(t) (((t)>255)?255:(((t)<0)?0:(t)))

        const unsigned char *yuv = source;
        int r1 = 0, g1 = 0, b1 = 0; // , a1 = 0;
        int r2 = 0, g2 = 0, b2 = 0; // a2 = 0;
        int u0 = 0, y0 = 0, v0 = 0, y1 = 0;

        unsigned char *rgba = dest;

        unsigned int padding = stride - width * 4;

//        std::cout << "rgba: " << rgba << std::endl;
//        std::cout << "yuv: " << yuv << std::endl;

        int counter = 0;

        // Loop through 4 bytes at a time
        for (unsigned int y = 0; y < height; y++) {
            counter++;
            std::cout << std::endl;
            for (unsigned int x = 0; x < width; x += 4) {

                std::cout << counter;
                u0 = (int) *yuv++;
                y0 = (int) *yuv++;
                v0 = (int) *yuv++;
                y1 = (int) *yuv++;
//                std::cout << v0 << std::endl;
                // u and v are +-0.5
                u0 -= 128;
                v0 -= 128;



                // Color space conversion for RGB
                r1 = CLAMPRGB((298 * y0 + 409 * v0 + 128) >> 8);
                g1 = CLAMPRGB((298 * y0 - 100 * u0 - 208 * v0 + 128) >> 8);
                b1 = CLAMPRGB((298 * y0 + 516 * u0 + 128) >> 8);
                r2 = CLAMPRGB((298 * y1 + 409 * v0 + 128) >> 8);
                g2 = CLAMPRGB((298 * y1 - 100 * u0 - 208 * v0 + 128) >> 8);
                b2 = CLAMPRGB((298 * y1 + 516 * u0 + 128) >> 8);

//                std::cout << r1 << std::endl;
//                std::cout << g1 << std::endl;
//                std::cout << b1 << std::endl;
//                std::cout << r2 << std::endl;
//                std::cout << g2 << std::endl;
//                std::cout << b2 << std::endl;


                *rgba++ = (unsigned char) r1;
                *rgba++ = (unsigned char) g1;
                *rgba++ = (unsigned char) b1;
                *rgba++ = (unsigned char) r2;
                *rgba++ = (unsigned char) g2;
                *rgba++ = (unsigned char) b2;
//                *rgba++ = 255;
            }
//            yuv += width * 2; // half width source data
//            yuv += padding; // if any
        }
    }
};


#endif //SIMPLENDI_CONVERTER_H
