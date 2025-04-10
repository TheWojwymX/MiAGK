//
// Created by TheWojwymX on 08.04.2025.
//

#include <cmath>
#include "../include/VertexProcessor.h"

VertexProcessor::VertexProcessor()
{

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
    Float4 clip = view2proj * vertex;

    if (clip.w != 0.0f)
    {
        return Float4(clip.x / clip.w, clip.y / clip.w, clip.z / clip.w, 1.0f);
    }
    return Float4(clip.x, clip.y, clip.z, 1.0f);
}


