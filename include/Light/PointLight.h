//
// Created by TheWojwymX on 23.04.2025.
//

#ifndef MIAGK_POINTLIGHT_H
#define MIAGK_POINTLIGHT_H


#include "Light.h"

class PointLight: public Light {
public:
    PointLight(const Float3 &position, const Float3 &ambient, const Float3 &diffuse, const Float3 &specular,
               float shininess);
    Float3 calculate(VertexProcessor& vp, const Float3& pointPosition, const Float3& normal) override;

};


#endif //MIAGK_POINTLIGHT_H
