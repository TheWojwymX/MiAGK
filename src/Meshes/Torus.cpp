//
// Created by TheWojwymX on 16.04.2025.
//

#include <algorithm>
#include "../../include/Meshes/Torus.h"


Torus::Torus(float majorRadius, float minorRadius, int slices, int stacks) : majorRadius(majorRadius), minorRadius(minorRadius), slices(slices), stacks(stacks)
{
    vertexProcessor = new VertexProcessor();
    vertexProcessor->setPerspective(120.0f, 800.0f / 600.0f, 0.1f, 1000.f);
    vertexProcessor->setLookAt(Float3(0, 0, 0), Float3(0, 0, -1), Float3(0, 1, 0));
}

void Torus::create() {
    float majorStep = 2.0f * M_PI / slices;
    float minorStep = 2.0f * M_PI / stacks;

    for (int i = 0; i <= slices; ++i) {
        float u = i * majorStep;
        float cosU = cos(u);
        float sinU = sin(u);

        for (int j = 0; j <= stacks; ++j) {
            float v = j * minorStep;
            float cosV = cos(v);
            float sinV = sin(v);

            float x = (majorRadius + minorRadius * cosV) * cosU;
            float y = (majorRadius + minorRadius * cosV) * sinU;
            float z = minorRadius * sinV;

            Float3 pos(x, y, z);
            Float3 normal(cosU * cosV, sinU * cosV, sinV);
            normal.normalize();

            float r = static_cast<float>(rand()) / RAND_MAX;
            float g = static_cast<float>(rand()) / RAND_MAX;
            float b = static_cast<float>(rand()) / RAND_MAX;

            vertices.push_back({ pos, normal, Float3(r, g, b) });
        }
    }

    for (int i = 0; i < slices; ++i) {
        for (int j = 0; j < stacks; ++j) {
            int current = i * (stacks + 1) + j;
            int next = (i + 1) % slices * (stacks + 1) + j;  // Wrap around at the end of slices
            int currentNext = i * (stacks + 1) + (j + 1) % stacks;  // Wrap around at the end of stacks
            int nextNext = (i + 1) % slices * (stacks + 1) + (j + 1) % stacks;

            // Bottom face triangle
            indices.push_back(Int3(current, next, currentNext));

            // Top face triangle
            indices.push_back(Int3(next, nextNext, currentNext));
        }
    }

    for (auto& v : vertices)
    {
        Float4 worldPos4 = vertexProcessor->obj2world * Float4(v.position.x, v.position.y, v.position.z, 1.0f);
        Float3 worldPos = worldPos4.toFloat3();

        Float4 worldNormal4 = vertexProcessor->obj2world * Float4(v.normal.x, v.normal.y, v.normal.z, 0.0f);
        Float3 worldNormal = worldNormal4.toFloat3();
        worldNormal.normalize();

        Float3 color(0, 0, 0);
        for (Light* light : vertexProcessor->getLights())
        {
            color = color + light->calculate(*vertexProcessor, worldPos, worldNormal) * v.vertexColor;
        }
        color.r = std::clamp(color.r, 0.0f, 1.0f);
        color.g = std::clamp(color.g, 0.0f, 1.0f);
        color.b = std::clamp(color.b, 0.0f, 1.0f);
        v.vertexColor = color;
    }
}