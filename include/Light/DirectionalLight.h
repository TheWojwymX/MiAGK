//
// Created by TheWojwymX on 22.04.2025.
//

#ifndef MIAGK_DIRECTIONALLIGHT_H
#define MIAGK_DIRECTIONALLIGHT_H
#pragma once

#include "Light.h"
#include "../VertexProcessor.h"

class DirectionalLight : public Light {
public:
    Float3 direction;

    DirectionalLight(const Float3 &position, const Float3 &ambient, const Float3 &diffuse, const Float3 &specular,
                     float shininess, const Float3 &direction);

    Float3 calculate(VertexProcessor& vp, const Float3& position, const Float3& normal) override;


};


#endif //MIAGK_DIRECTIONALLIGHT_H
