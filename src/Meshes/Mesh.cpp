//
// Created by TheWojwymX on 16.04.2025.
//

#include "../../include/Meshes/Mesh.h"

std::vector<Triangle> Mesh::generateTriangles() {
    std::vector<Triangle> triangles;
    for (const auto& idx : indices) {
        // Extract the three vertices from indices
        Vertex v1 = vertices[idx.v1];
        Vertex v2 = vertices[idx.v2];
        Vertex v3 = vertices[idx.v3];

        // Create the corresponding triangle with color and vertices
        triangles.push_back(Triangle(v1.position, v2.position, v3.position,
                                     v1.vertexColor, v2.vertexColor, v3.vertexColor));
    }
    return triangles;
}



