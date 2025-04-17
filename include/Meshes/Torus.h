//
// Created by TheWojwymX on 16.04.2025.
//

#ifndef MIAGK_TORUS_H
#define MIAGK_TORUS_H
#pragma once

#include "../../include/VertexProcessor.h"
#include "Mesh.h"

class Torus: public Mesh {
public:
    float majorRadius;
    float minorRadius;
    int slices;
    int stacks;

    Torus(float majorRadius = 1.0f, float minorRadius = 0.3f, int slices = 32, int stacks = 16);
    void create() override;
};


#endif //MIAGK_TORUS_H
