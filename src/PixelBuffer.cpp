#include <cfloat>
#include "../include/PixelBuffer.h"

PixelBuffer::PixelBuffer(unsigned int color, int width, int height)
{
    this->height = height;
    this->width = width;
    pixelBuffer = new unsigned int[height * width];
    zBuffer = new float[height * width];

    for(int i = 0; i < height * width; i++)
    {
        pixelBuffer[i] = color;
        zBuffer[i] = -FLT_MAX;
    }
}

void PixelBuffer::clearPixelBuffer(unsigned int color)
{
    for(int i = 0; i < height * width; i++)
    {
        pixelBuffer[i] = color;
    }
}

void PixelBuffer::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
    pixelBuffer = new unsigned int[width * height];
}

int PixelBuffer::getHeight() const
{
    return height;
}

int PixelBuffer::getWidth() const
{
    return width;
}

unsigned int *PixelBuffer::getPixelBuffer() const
{
    return pixelBuffer;
}

void PixelBuffer::setPixelBuffer(unsigned int *buffer) {
    PixelBuffer::pixelBuffer = buffer;
}

float *PixelBuffer::getZBuffer() const {
    return zBuffer;
}

void PixelBuffer::setZBuffer(float *zBuffer) {
    PixelBuffer::zBuffer = zBuffer;
}
