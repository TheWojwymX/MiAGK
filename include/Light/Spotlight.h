//
// Created by TheWojwymX on 22.04.2025.
//

#ifndef MIAGK_SPOTLIGHT_H
#define MIAGK_SPOTLIGHT_H
#pragma once

#include "Light.h"

class Spotlight: public Light {
public:
    Float3 direction;
    float cutOff;
    float outerCutOff;

    Spotlight(const Float3 &position, const Float3 &ambient, const Float3 &diffuse, const Float3 &specular,
              float shininess, const Float3 &direction, float cutOff, float outerCutOff);

    void calculate() override;
};


#endif //MIAGK_SPOTLIGHT_H
