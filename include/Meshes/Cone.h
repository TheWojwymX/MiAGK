//
// Created by TheWojwymX on 16.04.2025.
//

#ifndef MIAGK_CONE_H
#define MIAGK_CONE_H
#pragma once

#include "Mesh.h"
#include "../VertexProcessor.h"

class Cone : public Mesh {
public:
    float radius;
    int slices;
    int stacks;

    Cone(float radius = 1.0f, int slices = 16, int stacks = 16);
    void create() override;

};


#endif //MIAGK_CONE_H
