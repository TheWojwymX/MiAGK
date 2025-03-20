#include <iostream>
#include "../include/PixelBuffer.h"
#include "../include/ImageWriter.h"
#include "../include/mathTypes.h"
#include "../include/Rasterizer.h"

int main() {
    // color ARGB
    PixelBuffer* pixelBuffer = new PixelBuffer(0xff0000ff ,256,256);
    ImageWriter* imageWriter = new ImageWriter();
    Rasterizer* rasterizer = new Rasterizer(pixelBuffer);

    rasterizer->triangle( 0xffffffff,
                          {-0.9f, 0.5f, 0.0f},
                          {1.0f,1.0f,0.0f},
                          {1.0f,-1.0f,0.0f});

    rasterizer->triangle( 0xffffff00,
                          {-0.6f, -0.8f, 0.0f},
                          {0.7f,-0.8f,0.0f},
                          {0.1f,-0.98f,0.0f});

    imageWriter->saveToFile(pixelBuffer, "test.tga");

//////////////////////////////////////////////////////////////////////
    pixelBuffer->setSize(1024,1024);
    pixelBuffer->clearBuffer(0xffff0000);
    rasterizer->triangle( 0xffffffff,
                          {-0.9f, 0.5f, 0.0f},
                          {1.0f,1.0f,0.0f},
                          {1.0f,-1.0f,0.0f});

    rasterizer->triangle( 0xffffff00,
                          {-0.6f, -0.8f, 0.0f},
                          {0.7f,-0.8f,0.0f},
                          {0.1f,-0.98f,0.0f});

    imageWriter->saveToFile(pixelBuffer, "test2.tga");

    // Clean-up
    delete rasterizer;
    delete imageWriter;
    delete pixelBuffer;
}
