//
// Created by TheWojwymX on 16.04.2025.
//

#ifndef MIAGK_CYLINDER_H
#define MIAGK_CYLINDER_H
#pragma once

#include "Mesh.h"
#include "../../include/VertexProcessor.h"

class Cylinder: public Mesh {
public:
    float radius;
    float height;
    int slices;
    int stacks;

    Cylinder(float radius = 1.0f, float height = 1.0f, int slices = 16, int stacks = 1);
    void create() override;
};


#endif //MIAGK_CYLINDER_H
