//
// Created by TheWojwymX on 08.04.2025.
//

#ifndef MIAGK_VERTEXPROCESSOR_H
#define MIAGK_VERTEXPROCESSOR_H
#pragma once

#include "mathTypes.h"
#include "Meshes/Mesh.h"
#include "Light/Light.h"

class Light;

class VertexProcessor {
public:
    Float4x4 view2proj;
    Float4x4 world2view;
    Float4x4 obj2world;
    std::vector<Light*> lights;


    VertexProcessor();
    VertexProcessor(const Float4x4& view2proj);
    void setPerspective(float fovy, float aspect, float near, float far);
    Float4 projectVertex(const Float3& vertex);
    void setLookAt(Float3 eye, Float3 center, Float3 up);
    void mulByTranslation(Float3 v);
    void mulByScale(Float3 v);
    void mulByRotation(float a, Float3 v);
    std::vector<Float4> transformVertices(const std::vector<Vertex>& verts);
    void setIdentityTransform();                         // Reset obj2world
    void setTranslation(Float3 translation);
    void setScale(Float3 scale);
    void setTransform(Float3 scale, float a, Float3 rotation, Float3 translation);
    Float3 transformNormal(const Float3& normal);
    void addLight(Light* light);
    const std::vector<Light*>& getLights() const;





};


#endif //MIAGK_VERTEXPROCESSOR_H
