#include <algorithm>
#include "../include/Rasterizer.h"

Rasterizer::Rasterizer(PixelBuffer* pixelBuffer)
{
    this->pixelBuffer = pixelBuffer;
}

void Rasterizer::triangle(unsigned int color, Float3 v1, Float3 v2, Float3 v3)
{
    unsigned int* buffer = pixelBuffer->getBuffer();
    int width = pixelBuffer->getWidth();
    int height = pixelBuffer->getHeight();

    int v1x = (v1.x + 1) * width * 0.5f;
    int v1y = (v1.y + 1) * height * 0.5f;
    int v2x = (v2.x + 1) * width * 0.5f;
    int v2y = (v2.y + 1) * height * 0.5f;
    int v3x = (v3.x + 1) * width * 0.5f;
    int v3y = (v3.y + 1) * height * 0.5f;

    int maxx = std::max({v1x, v2x, v3x});
    int minx = std::min({v1x, v2x, v3x});
    int maxy = std::max({v1y, v2y, v3y});
    int miny = std::min({v1y, v2y, v3y});

    for(int i = minx; i < maxx; i++)
    {
        for (int j = miny; j < maxy; j++)
        {
            if (( (v1x - v2x) * (j - v1y) - (v1y - v2y) * (i - v1x) ) > 0
            && ( (v2x - v3x) * (j - v2y) - (v2y - v3y) * (i - v2x) ) > 0
            && ( (v3x - v1x) * (j - v3y) - (v3y - v1y) * (i - v3x) ) > 0)
            {
                buffer[i + j * width] = color;
            }
        }
    }
}

