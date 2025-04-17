//
// Created by TheWojwymX on 16.04.2025.
//

#include "../../Include/Meshes/Cone.h"

Cone::Cone(float radius, int slices, int stacks) : radius(radius), slices(slices), stacks(stacks)
{
    vertexProcessor = new VertexProcessor();
    vertexProcessor->setPerspective(120.0f, 800.0f / 600.0f, 0.1f, 1000.f);
    vertexProcessor->setLookAt(Float3(0, 0, 0), Float3(0, 0, -1), Float3(0, 1, 0));
}

void Cone::create() {
    float angleStep = 2.0f * M_PI / slices;
    float heightStep = 1.0f / stacks;

    // Generate side vertices
    for (int j = 0; j <= stacks; ++j) {
        float z = j * heightStep;              // Height [0,1]
        float r = radius * (1.0f - float(j) / stacks);  // Radius decreases linearly

        for (int i = 0; i < slices; ++i) {
            float angle = i * angleStep;
            float x = r * cos(angle);
            float y = r * sin(angle);

            Float3 pos(x, y, z);
            Float3 normal(x, y, radius);  // Approximated normal
            normal.normalize();

            float r = static_cast<float>(rand()) / RAND_MAX;
            float g = static_cast<float>(rand()) / RAND_MAX;
            float b = static_cast<float>(rand()) / RAND_MAX;

            vertices.push_back({ pos, normal, Float3(r, g, b) });
        }
    }

    // Apex vertex (used by top triangles if needed)
    int apexIndex = vertices.size();
    vertices.push_back({ Float3(0.0f, 0.0f, 1.0f), Float3(0, 0, 1), Float3(1, 0, 0) });

    // Side indices (two triangles per quad)
    for (int j = 0; j < stacks; ++j) {
        for (int i = 0; i < slices; ++i) {
            int current = j * slices + i;
            int next = j * slices + (i + 1) % slices;
            int upper = (j + 1) * slices + i;
            int upperNext = (j + 1) * slices + (i + 1) % slices;

            // Lower triangle
            indices.push_back(Int3(current, next, upper));

            // Upper triangle
            indices.push_back(Int3(next, upperNext, upper));
        }
    }

    // Base center
    int baseCenterIndex = vertices.size();
    vertices.push_back({ Float3(0.0f, 0.0f, 0.0f), Float3(0, 0, -1), Float3(0.0, 0.0, 0.0) });

    // Base ring (last stack ring)
    int baseRingStart = 0;

    for (int i = 0; i < slices; ++i) {
        int current = baseRingStart + i;
        int next = baseRingStart + (i + 1) % slices;
        indices.push_back(Int3(next, current, baseCenterIndex));

        vertices[current].vertexColor = Float3(0.0f, 0.0f, 0.0f);
    }
}
