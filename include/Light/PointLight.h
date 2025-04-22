//
// Created by TheWojwymX on 22.04.2025.
//

#ifndef MIAGK_POINTLIGHT_H
#define MIAGK_POINTLIGHT_H
#pragma once

#include "Light.h"

class PointLight: public Light {
public:

    PointLight(const Float3 &position, const Float3 &ambient, const Float3 &diffuse, const Float3 &specular,
               float shininess);

    void calculate() override;

};


#endif //MIAGK_POINTLIGHT_H
