#include <iostream>
#include "../include/PixelBuffer.h"
#include "../include/ImageWriter.h"
#include "../include/mathTypes.h"
#include "../include/Rasterizer.h"

int main() {
    // color ARGB
    PixelBuffer* pixelBuffer = new PixelBuffer(0xff0000ff ,800,600);
    ImageWriter* imageWriter = new ImageWriter();
    Rasterizer* rasterizer = new Rasterizer(pixelBuffer);
    VertexProcessor* vertexProcessor = new VertexProcessor();

    vertexProcessor->setPerspective(90.0f, 800.0f / 600.0f, 0.1f, 1000.f);

    Triangle* t1 = new Triangle(vertexProcessor->projectVertex(Float3(-50.0f, 0.f, -500.0f)).toFloat3(),
                                vertexProcessor->projectVertex(Float3(50.0f,0.0f,-500.0f)).toFloat3(),
                                vertexProcessor->projectVertex(Float3(0.0f,-50.0f,-500.0f)).toFloat3(),
                                Float3(1.0f, 0.0f, 0.0), Float3(0.0f,1.0f,0.0f), Float3(0.0f,1.0f,0.0f));
    Triangle* t2 = new Triangle(vertexProcessor->projectVertex(Float3(-75.0f, 25.f, -500.0f)).toFloat3(),
                                vertexProcessor->projectVertex(Float3(0.0f,100.0f,-500.0f)).toFloat3(),
                                vertexProcessor->projectVertex(Float3(75.0f,25.0f,-500.0f)).toFloat3(),
                                Float3(1.0f, 1.0f, 0.0), Float3(0.0f,1.0f,1.0f), Float3(1.0f,0.0f,1.0f));

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
