//
// Created by TheWojwymX on 22.04.2025.
//

#ifndef MIAGK_LIGHT_H
#define MIAGK_LIGHT_H
#pragma once

#include "../mathTypes.h"

class Light {
public:
    Float3 position;
    Float3 ambient;
    Float3 diffuse;
    Float3 specular;
    float shininess;

    Light(const Float3 &position, const Float3 &ambient, const Float3 &diffuse, const Float3 &specular,
          float shininess);

    virtual void calculate() = 0;

};


#endif //MIAGK_LIGHT_H
