//
// Created by TheWojwymX on 23.04.2025.
//

#ifndef MIAGK_SPOTLIGHT_H
#define MIAGK_SPOTLIGHT_H
#pragma once

#include "Light.h"

class Spotlight: public Light {
public:
    Float3 direction;
    float innerAngle;
    float outerAngle;

    Spotlight(const Float3 &position, const Float3 &ambient, const Float3 &diffuse, const Float3 &specular,
              float shininess, const Float3 &direction, float innerAngle, float outerAngle);

    Float3 calculate(VertexProcessor& vp, const Float3& pointPosition, const Float3& normal) override;

};


#endif //MIAGK_SPOTLIGHT_H
