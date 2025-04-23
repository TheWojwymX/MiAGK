//
// Created by TheWojwymX on 23.04.2025.
//

#include "../../include/Light/PointLight.h"

PointLight::PointLight(const Float3 &position, const Float3 &ambient, const Float3 &diffuse, const Float3 &specular,
                       float shininess) : Light(position, ambient, diffuse, specular, shininess) {

}

Float3 PointLight::calculate(VertexProcessor& vp, const Float3& pointPosition, const Float3& normal)
{
    // 1. N - normal do przestrzeni widoku
    Float3 N = (vp.world2view * Float4(normal.x, normal.y, normal.z, 0.0f)).toFloat3();
    N.normalize();

    // 2. V - wektor do kamery (przeciwny do przekształconej pozycji wierzchołka)
    Float3 posView = (vp.world2view * Float4(pointPosition.x, pointPosition.y, pointPosition.z, 1.0f)).toFloat3();
    Float3 V = {-posView.x, -posView.y, -posView.z};
    V.normalize();

    // 3. L - kierunek od światła do fragmentu (pozycja fragmentu - pozycja światła)
    Float3 lightPosView = (vp.world2view * Float4(position.x, position.y, position.z, 1.0f)).toFloat3();
    Float3 L = (lightPosView - pointPosition);
    L.normalize();

    // 4. R - odbity wektor
    Float3 R = (2.0f * N.dot(L) * N - L);
    R.normalize();

    // 5. Diffuse - obliczanie współczynnika diffuse (oświetlenie zależne od kąta)
    float diff = std::max(N.dot(L), 0.0f);

    // 6. Specular - obliczanie współczynnika specular (współczynnik lustrzany)
    float spec = 0.0f;
    if (diff > 0.0f) {
        spec = pow(std::max(R.dot(V), 0.0f), shininess);
    }


    // 7. Zwróć ostateczny kolor z uwzględnieniem zasięgu światła
    return (ambient + diffuse * diff + specular * spec);
}

