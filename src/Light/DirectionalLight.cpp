//
// Created by TheWojwymX on 22.04.2025.
//

#include "../../include/Light/DirectionalLight.h"

Float3 DirectionalLight::calculate(VertexProcessor& vp, const Float3& position, const Float3& normal)
{
    // 1. N - normal do przestrzeni widoku
    Float3 N = (vp.world2view * Float4(normal.x, normal.y, normal.z, 0.0f)).toFloat3();
    N.normalize();

    // 2. V - wektor do kamery (przeciwny do przekształconej pozycji wierzchołka)
    Float3 posView = (vp.world2view * Float4(position.x, position.y, position.z, 1.0f)).toFloat3();
    Float3 V = {-posView.x, -posView.y, -posView.z};
    V.normalize();

    // 3. L - kierunek światła do przestrzeni widoku
    Float3 L = (vp.world2view * Float4(-direction.x, -direction.y, -direction.z, 0.0f)).toFloat3();
    L.normalize();

    // 4. R - odbity wektor
    Float3 R = (2.0f * N.dot(L) * N - L);
    R.normalize();

    // 5. Diffuse
    float diff = std::max(N.dot(L), 0.0f);

    // 6. Specular
    float spec = 0.0f;
    if (diff > 0.0f) {
        spec = pow(std::max(R.dot(V), 0.0f), shininess);
    }

    return ambient + diffuse * diff + specular * spec;
}

DirectionalLight::DirectionalLight(const Float3 &position, const Float3 &ambient, const Float3 &diffuse,
                                   const Float3 &specular, float shininess, const Float3 &direction) :
                                   Light(position,ambient,diffuse,specular,shininess),direction(direction)
                                   {

                                   }
