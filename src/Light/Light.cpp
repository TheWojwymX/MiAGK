//
// Created by TheWojwymX on 22.04.2025.
//

#include "../../include/Light/Light.h"

Light::Light(const Float3 &position, const Float3 &ambient, const Float3 &diffuse, const Float3 &specular,
             float shininess) : position(position), ambient(ambient), diffuse(diffuse), specular(specular),
                                shininess(shininess) {}
