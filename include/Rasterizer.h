#ifndef MIAGK_RASTERIZER_H
#define MIAGK_RASTERIZER_H
#include "../include/mathTypes.h"
#include "../include/PixelBuffer.h"


class Rasterizer {
private:
    PixelBuffer* pixelBuffer;

public:
    Rasterizer(PixelBuffer* pixelBuffer);
    void triangle(unsigned int color, Float3 v1, Float3 v2, Float3 v3);

};


#endif //MIAGK_RASTERIZER_H
