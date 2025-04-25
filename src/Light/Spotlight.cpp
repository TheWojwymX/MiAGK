//
// Created by TheWojwymX on 23.04.2025.
//

#include "../../include/Light/Spotlight.h"

Spotlight::Spotlight(const Float3 &position, const Float3 &ambient, const Float3 &diffuse,
                     const Float3 &specular, float shininess, const Float3 &direction, float innerAngle,
                     float outerAngle) : Light(position,ambient,diffuse,specular,shininess),direction(direction),
                     innerAngle(innerAngle),outerAngle(outerAngle) {

}

Float3 Spotlight::calculate(VertexProcessor& vp, const Float3& pointPosition, const Float3& normal)
{
    float innerRadians = innerAngle * M_PI / 180.0f;
    float outerRadians = outerAngle * M_PI / 180.0f;

    // 1. N - normal in view space
    Float3 N = (vp.world2view * Float4(normal.x, normal.y, normal.z, 0.0f)).toFloat3();
    N.normalize();

    // 2. V - view vector (opposite of the transformed vertex position)
    Float3 posView = (vp.world2view * Float4(pointPosition.x, pointPosition.y, pointPosition.z, 1.0f)).toFloat3();
    Float3 V = {-posView.x, -posView.y, -posView.z};
    V.normalize();

    // 3. L - light direction in world space (from the light position to the point position)
    Float3 lightToPoint = position - pointPosition;  // Direction from light to point
    lightToPoint.normalize();

    // 4. L - transformed to view space
    Float3 L = (vp.world2view * Float4(lightToPoint.x, lightToPoint.y, lightToPoint.z, 0.0f)).toFloat3();
    L.normalize();

    // 5. Calculate the angle between the light direction and the direction to the point
    float cosTheta = L.dot(N);

    if (cosTheta < cos(outerRadians)) {
        // Point is outside the spotlight cone, return ambient color
        return ambient;
    }

    // 6. If the point is within the spotlight's inner cone, use full diffuse and specular contribution
    float spotFactor = 1.0f;
    if (cosTheta < cos(innerRadians)) {
        // Blend the intensity based on the angle within the cone
        spotFactor = pow(cosTheta, 20); // Adjust 20 for smoothness of transition (falloff)
    }

    // 7. R - reflected vector
    Float3 R = (2.0f * N.dot(L) * N - L);
    R.normalize();

    // 8. Diffuse and Specular Components
    float diff = std::max(N.dot(L), 0.0f);
    float spec = 0.0f;
    if (diff > 0.0f) {
        spec = pow(std::max(R.dot(V), 0.0f), shininess);
    }

    // 9. Apply spotFactor to diffuse and specular
    Float3 color = ambient + diffuse * diff * spotFactor + specular * spec * spotFactor;

    // 10. Return final color
    return color;


}



