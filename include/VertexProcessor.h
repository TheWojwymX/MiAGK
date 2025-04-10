//
// Created by TheWojwymX on 08.04.2025.
//

#ifndef MIAGK_VERTEXPROCESSOR_H
#define MIAGK_VERTEXPROCESSOR_H


#include "mathTypes.h"

class VertexProcessor {
public:
    Float4x4 view2proj;

    VertexProcessor();
    VertexProcessor(const Float4x4& view2proj);
    void setPerspective(float fovy, float aspect, float near, float far);
    Float4 projectVertex(const Float3& vertex);



};


#endif //MIAGK_VERTEXPROCESSOR_H
