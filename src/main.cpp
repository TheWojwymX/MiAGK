#include <iostream>
#include "../include/PixelBuffer.h"
#include "../include/ImageWriter.h"
#include "../include/mathTypes.h"
#include "../include/Rasterizer.h"

int main() {
    // color ARGB
    PixelBuffer* pixelBuffer = new PixelBuffer(0xff0000ff ,512,512);
    ImageWriter* imageWriter = new ImageWriter();
    Rasterizer* rasterizer = new Rasterizer(pixelBuffer);

//    Triangle* t1 = new Triangle(Float3(-1.0f, -0.5f, 0.0f), Float3(0.0f,0.5f,0.0f), Float3(0.1f,-0.2f,0.0f),
//                                Float3(1.0f, 0.0f, 0.0f), Float3(0.0f,1.0f,0.0f), Float3(0.0f,1.0f,0.0f));
//    Triangle* t2 = new Triangle(Float3(0.1f, -0.2f, 0.0f), Float3(0.0f,0.5f,0.0f), Float3(0.8f,0.3f,0.0f),
//                                Float3(1.0f, 1.0f, 0.0f), Float3(0.0f,1.0f,1.0f), Float3(1.0f,1.0f,1.0f));

    Triangle* t1 = new Triangle(Float3(-1.0f, 0.0f, 0.0f), Float3(0.0f,1.0f,0.0f), Float3(1.0f,0.0f,0.0f),
                                Float3(1.0f, 0.0f, 0.0f), Float3(0.0f,1.0f,0.0f), Float3(0.0f,1.0f,0.0f));
    Triangle* t2 = new Triangle(Float3(-1.0f, -0.3f, -0.5f), Float3(0.0f,0.8f,0.5f), Float3(1.0f,-0.3f,-0.5f),
                                Float3(1.0f, 1.0f, 0.0f), Float3(0.0f,1.0f,1.0f), Float3(0.0f,1.0f,1.0f));

    rasterizer->addTriangle(t1);
    rasterizer->addTriangle(t2);
    rasterizer->fillTriangles();

    imageWriter->saveToFile(pixelBuffer, "test.tga");

    // Clean-up
    delete rasterizer;
    delete t1;
    delete imageWriter;
    delete pixelBuffer;
}
