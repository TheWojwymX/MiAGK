//
// Created by TheWojwymX on 22.04.2025.
//

#include "../../include/Light/PointLight.h"

void PointLight::calculate()
{

}

PointLight::PointLight(const Float3 &position, const Float3 &ambient, const Float3 &diffuse, const Float3 &specular,
                       float shininess) : Light(position, ambient, diffuse, specular, shininess)
                       {

                       }

