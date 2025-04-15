//
// Created by TheWojwymX on 16.04.2025.
//

#ifndef MIAGK_MESH_H
#define MIAGK_MESH_H
#pragma once

#include <vector>
#include "mathTypes.h"
#include "Triangle.h"

struct Vertex {
    Float3 position;
    Float3 normal;
    Float3 vertexColor;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<Int3> indices;

    virtual void create() = 0;
    std::vector<Triangle> generateTriangles();
};


#endif //MIAGK_MESH_H
