//
// Created by TheWojwymX on 16.04.2025.
//

#include <vector>
#include <ctime>
#include "../../include/Meshes/Sphere.h"

Sphere::Sphere(float radius, int slices, int stacks)
{
    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;
}

void Sphere::create()
{
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

            Float3 pos = Float3(x, y, z) * radius;
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
}




