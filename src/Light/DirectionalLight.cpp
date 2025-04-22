//
// Created by TheWojwymX on 22.04.2025.
//

#include "../../include/Light/DirectionalLight.h"

void DirectionalLight::calculate()
{

}

DirectionalLight::DirectionalLight(const Float3 &position, const Float3 &ambient, const Float3 &diffuse,
                                   const Float3 &specular, float shininess, const Float3 &direction) :
                                   Light(position,ambient,diffuse,specular,shininess),direction(direction)
                                   {

                                   }
