
#ifndef MIAGK_TRIANGLE_H
#define MIAGK_TRIANGLE_H
#pragma once

#include "../mathTypes.h"
#include "../VertexProcessor.h"

class VertexProcessor;
class Mesh;

class VertexProcessor;

class Triangle {
public:
    Float3 v1, v2, v3;
    Float3 c1, c2, c3;
    Float3 n1, n2, n3;
    Float3 w1, w2, w3;
    Float3 uv1, uv2, uv3;
    VertexProcessor* vp;
    bool usePhongShading = false;
    bool useTexture = false;
    unsigned int* textureData = nullptr;
    int texWidth = 0, texHeight = 0;
    int textureType = 1;

    Triangle(Float3 v1, Float3 v2, Float3 v3, Float3 c1, Float3 c2, Float3 c3);
};


#endif //MIAGK_TRIANGLE_H
