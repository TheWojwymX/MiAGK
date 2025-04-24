
#ifndef MIAGK_TRIANGLE_H
#define MIAGK_TRIANGLE_H
#pragma once

#include "../mathTypes.h"
#include "../VertexProcessor.h"

class VertexProcessor;
class Mesh;

class Triangle {
public:
    bool isGouraud = true;
    VertexProcessor* vp;

    Float3 v1, v2, v3;
    Float3 c1, c2, c3;

    Float3 n1, n2, n3;
    Float3 p1, p2, p3;

    Triangle(Float3 v1, Float3 v2, Float3 v3, Float3 c1, Float3 c2, Float3 c3);
};


#endif //MIAGK_TRIANGLE_H
