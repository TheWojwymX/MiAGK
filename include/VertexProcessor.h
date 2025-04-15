//
// Created by TheWojwymX on 08.04.2025.
//

#ifndef MIAGK_VERTEXPROCESSOR_H
#define MIAGK_VERTEXPROCESSOR_H


#include "mathTypes.h"

class VertexProcessor {
public:
    Float4x4 view2proj;
    Float4x4 world2view;
    Float4x4 obj2world;

    VertexProcessor();
    VertexProcessor(const Float4x4& view2proj);
    void setPerspective(float fovy, float aspect, float near, float far);
    Float4 projectVertex(const Float3& vertex);
    void setLookAt(Float3 eye, Float3 center, Float3 up);
    void mulByTranslation(Float3 v);
    void mulByScale(Float3 v);
    void mulByRotation(float a, Float3 v);
    

};


#endif //MIAGK_VERTEXPROCESSOR_H
