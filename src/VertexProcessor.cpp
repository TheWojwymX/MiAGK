//
// Created by TheWojwymX on 08.04.2025.
//

#include <cmath>
#include "../include/VertexProcessor.h"

VertexProcessor::VertexProcessor()
{
    obj2world.setAsIdentity();
    view2proj.setAsIdentity();
    world2view.setAsIdentity();
}

VertexProcessor::VertexProcessor(const Float4x4 &view2proj)
{
    this->view2proj = view2proj;
}

void VertexProcessor::setPerspective(float fovy, float aspect, float near, float far)
{
    fovy *= M_PI / 360;
    float f = cos(fovy) / sin(fovy);

    view2proj[0] = Float4(f/aspect, 0, 0, 0);
    view2proj[1] = Float4(0, f, 0, 0);
    view2proj[2] = Float4(0, 0, (far + near)/(near - far), -1);
    view2proj[3] = Float4(0, 0, (2 * far * near)/(near - far), 0);
}

Float4 VertexProcessor::projectVertex(const Float3& vertex)
{
    Float4 world = obj2world * Float4(vertex.x, vertex.y, vertex.z, 1.0f);
    Float4 view = world2view * world;
    Float4 clip = view2proj * view;

    if (clip.w != 0.0f) {
        clip.x /= clip.w;
        clip.y /= clip.w;
        clip.z /= clip.w;
        clip.w = 1.0f;
    }

    return clip;
}

void VertexProcessor::mulByScale(Float3 v)
{
    Float4x4 m = Float4x4(
            Float4(v.x, 0, 0, 0),
            Float4(0, v.y, 0, 0),
            Float4(0, 0, v.z, 0),
            Float4(0, 0, 0, 1)
    );

    obj2world = m * obj2world;

}

void VertexProcessor::setLookAt(Float3 eye, Float3 center, Float3 up)
{
    Float3 f = center - eye;
    f.normalize();
    Float3 Up = up;
    Up.normalize();
    Float3 s = f.cross(Up);
    Float3 u = s.cross(f);

    world2view[0] = Float4(s.x, u.x, -f.x, 0);
    world2view[1] = Float4(s.y, u.y, -f.y, 0);
    world2view[2] = Float4(s.z, u.z, -f.z, 0);
    world2view[3] = Float4(0, 0, 0, 1);

    Float4x4 m;
    m.setAsIdentity();
    m[3] = Float4(-eye.x, -eye.y, -eye.z, 1.0f);
    world2view = world2view * m;
}

void VertexProcessor::mulByTranslation(Float3 v)
{
    Float4x4 m(Float4(1, 0, 0, v.x),
               Float4(0, 1, 0, v.y),
               Float4(0, 0, 1, v.z),
               Float4(0, 0, 0, 1));
    obj2world = m * obj2world;
}

void VertexProcessor::mulByRotation(float a, Float3 v) {
    float s = sin(a * M_PI / 180);
    float c = cos(a * M_PI / 180);
    float one_c = 1.0f - c;
    v.normalize();

    float x = v.x;
    float y = v.y;
    float z = v.z;

    Float4x4 m;
    m[0] = Float4(x * x * one_c + c, x * y * one_c - z * s, x * z * one_c + y * s, 0.0f);
    m[1] = Float4(y * x * one_c + z * s, y * y * one_c + c, y * z * one_c - x * s, 0.0f);
    m[2] = Float4(x * z * one_c - y * s, y * z * one_c + x * s, z * z * one_c + c, 0.0f);
    m[3] = Float4(0.0f, 0.0f, 0.0f, 1.0f);

    obj2world = m * obj2world;
}









