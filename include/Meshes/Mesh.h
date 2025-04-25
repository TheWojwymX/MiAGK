//
// Created by TheWojwymX on 16.04.2025.
//

#ifndef MIAGK_MESH_H
#define MIAGK_MESH_H
#pragma once

#include "../mathTypes.h"
#include <vector>

struct Vertex {
    Float3 position;
    Float3 normal;
    Float3 vertexColor;
};

class VertexProcessor;
class Triangle;

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<Int3> indices;
    VertexProcessor* vertexProcessor;
    bool isGouraud = true;

    virtual void create() = 0;
};


#endif //MIAGK_MESH_H
