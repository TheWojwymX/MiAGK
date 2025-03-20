#include "../include/PixelBuffer.h"

PixelBuffer::PixelBuffer(unsigned int color, int height, int width)
{
    this->height = height;
    this->width = width;
    buffer = new unsigned int[height * width];

    for(int i = 0; i < height * width; i++)
    {
        buffer[i] = color;
    }
}

void PixelBuffer::clearBuffer(unsigned int color)
{
    for(int i = 0; i < height * width; i++)
    {
        buffer[i] = color;
    }
}

void PixelBuffer::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
    buffer = new unsigned int[width * height];
}

int PixelBuffer::getHeight() const
{
    return height;
}

int PixelBuffer::getWidth() const
{
    return width;
}

unsigned int *PixelBuffer::getBuffer() const
{
    return buffer;
}

void PixelBuffer::setBuffer(unsigned int *buffer) {
    PixelBuffer::buffer = buffer;
}
