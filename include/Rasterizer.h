#ifndef MIAGK_RASTERIZER_H
#define MIAGK_RASTERIZER_H

#include <vector>
#include "../include/mathTypes.h"
#include "../include/PixelBuffer.h"
#include "Triangle.h"


class Rasterizer {
private:
    PixelBuffer* pixelBuffer;
    std::vector<Triangle*> triangles;

public:
    Rasterizer(PixelBuffer* pixelBuffer);
    void addTriangle(Triangle* t1);
    void fillTriangles();

};


#endif //MIAGK_RASTERIZER_H
