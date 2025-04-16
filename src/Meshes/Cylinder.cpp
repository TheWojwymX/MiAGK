//
// Created by TheWojwymX on 16.04.2025.
//

#include "../../include/Meshes/Cylinder.h"

Cylinder::Cylinder(float radius, float height, int slices, int stacks)
        : radius(radius), height(height), slices(slices), stacks(stacks) {}

void Cylinder::create() {
    float angleStep = 2.0f * M_PI / slices;
    float heightStep = height / stacks;

    // === Side Vertices ===
    for (int j = 0; j <= stacks; ++j) {
        float z = j * heightStep;

        for (int i = 0; i < slices; ++i) {
            float angle = i * angleStep;
            float x = radius * cos(angle);
            float y = radius * sin(angle);
            Float3 normal = Float3(x, y, 0);
            normal.normalize();

            float r = static_cast<float>(rand()) / RAND_MAX;
            float g = static_cast<float>(rand()) / RAND_MAX;
            float b = static_cast<float>(rand()) / RAND_MAX;

            vertices.push_back({ Float3(x, y, z), normal, Float3(r, g, b) });
        }
    }

    // === Side Indices (Quads split into two triangles) ===
    for (int j = 0; j < stacks; ++j) {
        for (int i = 0; i < slices; ++i) {
            int curr = j * slices + i;
            int next = j * slices + (i + 1) % slices;
            int upper = (j + 1) * slices + i;
            int upperNext = (j + 1) * slices + (i + 1) % slices;

            indices.push_back(Int3(curr, next, upper));
            indices.push_back(Int3(next, upperNext, upper));
        }
    }

    // === Bottom Cap ===
    int bottomCenterIndex = vertices.size();
    vertices.push_back({ Float3(0, 0, 0), Float3(0, 0, -1), Float3(0, 0, 0) });

    int bottomRingStart = vertices.size();
    for (int i = 0; i < slices; ++i) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        vertices.push_back({ Float3(x, y, 0), Float3(0, 0, -1), Float3(0, 0, 0) });
    }

    for (int i = 0; i < slices; ++i) {
        int curr = bottomRingStart + i;
        int next = bottomRingStart + (i + 1) % slices;
        indices.push_back(Int3(next, curr, bottomCenterIndex));
    }

    // === Top Cap ===
    int topCenterIndex = vertices.size();
    vertices.push_back({ Float3(0, 0, height), Float3(0, 0, 1), Float3(0, 0, 0) });

    int topRingStart = vertices.size();
    for (int i = 0; i < slices; ++i) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        vertices.push_back({ Float3(x, y, height), Float3(0, 0, 1), Float3(0, 0, 0) });
    }

    for (int i = 0; i < slices; ++i) {
        int curr = topRingStart + i;
        int next = topRingStart + (i + 1) % slices;
        indices.push_back(Int3(topCenterIndex, curr, next));
    }
}
