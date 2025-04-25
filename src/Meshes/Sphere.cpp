//
// Created by TheWojwymX on 16.04.2025.
//

#include <vector>
#include <ctime>
#include <algorithm>
#include "../../include/Meshes/Sphere.h"

Sphere::Sphere(float radius, int slices, int stacks)
{
    vertexProcessor = new VertexProcessor();
    vertexProcessor->setPerspective(120.0f, 800.0f / 600.0f, 0.1f, 1000.f);
    vertexProcessor->setLookAt(Float3(0, 0, 0), Float3(0, 0, -1), Float3(0, 1, 0));

    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;
}

void Sphere::create() {
    vertices.clear();
    indices.clear();

    srand(static_cast<unsigned int>(time(0)));


    for (int stack = 0; stack <= stacks; ++stack) {
        float phi = M_PI * stack / stacks;
        float y = cos(phi);
        float r = sin(phi);

        for (int slice = 0; slice <= slices; ++slice) {
            float theta = 2.0f * M_PI * slice / slices;
            float x = r * cos(theta);
            float z = r * sin(theta);

            Float3 pos = Float3(-x, -y, -z) * radius;
            Float3 pos_norm = pos;
            pos_norm.normalize();

            float r = static_cast<float>(rand()) / RAND_MAX;
            float g = static_cast<float>(rand()) / RAND_MAX;
            float b = static_cast<float>(rand()) / RAND_MAX;

            vertices.push_back({pos, pos_norm, Float3(r, g, b)});
        }
    }

    for (int stack = 0; stack < stacks; ++stack) {
        for (int slice = 0; slice < slices; ++slice) {
            int a = stack * (slices + 1) + slice;
            int b = a + slices + 1;

            indices.push_back(Int3(a, b, a + 1));
            indices.push_back(Int3(b, b + 1, a + 1));
        }
    }

    if (usePhongShading) return;

    for (auto &v: vertices) {
        Float4 worldPos4 = vertexProcessor->obj2world * Float4(v.position.x, v.position.y, v.position.z, 1.0f);
        Float3 worldPos = worldPos4.toFloat3();

        Float4 worldNormal4 = vertexProcessor->obj2world * Float4(v.normal.x, v.normal.y, v.normal.z, 0.0f);
        Float3 worldNormal = worldNormal4.toFloat3();
        worldNormal.normalize();

        // Gouraud shading: Update vertex colors
        Float3 color(0, 0, 0);
        for (Light *light: vertexProcessor->getLights()) {
            color = color + light->calculate(*vertexProcessor, worldPos, worldNormal) * v.vertexColor;
        }

        // Clamp color to [0, 1]
        color.r = std::clamp(color.r, 0.0f, 1.0f);
        color.g = std::clamp(color.g, 0.0f, 1.0f);
        color.b = std::clamp(color.b, 0.0f, 1.0f);
        v.vertexColor = color;
    }
}




