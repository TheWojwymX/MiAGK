//
// Created by TheWojwymX on 22.04.2025.
//

#include "../../include/Light/Spotlight.h"

void Spotlight::calculate()
{

}

Spotlight::Spotlight(const Float3 &position, const Float3 &ambient, const Float3 &diffuse,
                     const Float3 &specular, float shininess, const Float3 &direction, float cutOff,
                     float outerCutOff) : Light(position,ambient,diffuse,specular,shininess),direction(direction),
                     cutOff(cutOff),outerCutOff(outerCutOff) {}

