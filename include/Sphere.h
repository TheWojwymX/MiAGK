//
// Created by TheWojwymX on 16.04.2025.
//

#ifndef MIAGK_SPHERE_H
#define MIAGK_SPHERE_H


#include "Mesh.h"
#include "VertexProcessor.h"

class Sphere: public Mesh {
public:
    float radius;
    int slices;
    int stacks;

    Sphere(float radius = 1.0f, int slices = 16, int stacks = 16);
    void create() override;
    std::vector <Float4> getTransformedVertices(VertexProcessor &processor);
};


#endif //MIAGK_SPHERE_H
