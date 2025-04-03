#include <algorithm>
#include <iostream>
#include "../include/Rasterizer.h"

Rasterizer::Rasterizer(PixelBuffer* pixelBuffer)
{
    this->pixelBuffer = pixelBuffer;
}

void Rasterizer::fillTriangles()
{
    unsigned int* buffer = pixelBuffer->getBuffer();
    int width = pixelBuffer->getWidth();
    int height = pixelBuffer->getHeight();

    for(int i = 0; i < triangles.size(); i++)
    {
        int v1x = (triangles[i]->v1.x + 1) * width * 0.5f;
        int v1y = (triangles[i]->v1.y + 1) * height * 0.5f;
        int v2x = (triangles[i]->v2.x + 1) * width * 0.5f;
        int v2y = (triangles[i]->v2.y + 1) * height * 0.5f;
        int v3x = (triangles[i]->v3.x + 1) * width * 0.5f;
        int v3y = (triangles[i]->v3.y + 1) * height * 0.5f;

        int dx12 = v1x - v2x;
        int dx23 = v2x - v3x;
        int dx31 = v3x - v1x;

        int dy12 = v1y - v2y;
        int dy23 = v2y - v3y;
        int dy31 = v3y - v1y;

        int maxx = std::max({v1x, v2x, v3x});
        int minx = std::min({v1x, v2x, v3x});
        int maxy = std::max({v1y, v2y, v3y});
        int miny = std::min({v1y, v2y, v3y});

        minx = std::max(minx, 0);
        maxx = std::min(maxx, width-1);
        miny = std::max(miny, 0);
        maxy = std::min(maxy, height-1);

        for(int x = minx; x < maxx; x++)
        {
            for (int y = miny; y < maxy; y++)
            {
                if (( dx12 * (y - v1y) - dy12 * (x - v1x) ) > 0
                    && ( dx23 * (y - v2y) - dy23 * (x - v2x) ) > 0
                    && ( dx31 * (y - v3y) - dy31 * (x - v3x) ) > 0)
                {
                    float k1 = float ((dy23 * (x - v3x)) + (-dx23 * (y - v3y))) / ( dy23 * (-dx31) + (-dx23) * (-dy31) );
                    float k2 = float ((dy31 * (x - v3x)) + (-dx31 * (y - v3y))) / ( dy31 * dx23 + (-dx31) * dy23 );
                    float k3 = 1 - k1 - k2;

                    Float3 color = triangles[i]->c1 * k1 + triangles[i]->c2 * k2 + triangles[i]->c3 * k3;
                    unsigned int hexColor = (0xFF << 24) | ((unsigned char)(color.r * 255.0f) << 16)
                            | ((unsigned char)(color.g * 255.0f) << 8) | (unsigned char)(color.b * 255.0f) ;
                    buffer[x + y * width] = hexColor;
                }
            }
        }
    }
}

void Rasterizer::addTriangle(Triangle* t1)
{
    triangles.push_back(t1);
}

