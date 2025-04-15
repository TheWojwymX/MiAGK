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
    VertexProcessor* vp = new VertexProcessor();
    VertexProcessor* vp2 = new VertexProcessor();

    vp->setPerspective(120.0f, 800.0f / 600.0f, 0.1f, 1000.f);
    vp2->setPerspective(120.0f, 800.0f / 600.0f, 0.1f, 1000.f);
    vp->setLookAt(Float3(0, 0, 0), Float3(0, 0, -1), Float3(0, 1, 0));
    vp2->setLookAt(Float3(0, 0, 0), Float3(0, 0, -1), Float3(0, 1, 0));

    Triangle* t1 = new Triangle(  Float3(-0.5f, 0.5f, 0),
                                           Float3(0.5f, 0.5f, 0),
                                           Float3(0, -0.5f, 0),
                                           Float3(1, 0, 1),
                                           Float3(0, 1, 1),
                                           Float3(0, 1, 1));

    Triangle* t2 = new Triangle(  Float3(-0.5f, -0.55f, 0),
                                  Float3(0.5f, -0.55f, 0),
                                  Float3(0, -0.85f, 0),
                                  Float3(1, 0, 1),
                                  Float3(0, 1, 0),
                                  Float3(1, 1, 1));

//    vp->mulByTranslation(Float3(2, 0, 0));
    vp->mulByRotation(90.0f, Float3(0.0f, 0.0f, 0.5f));
//    vp->mulByScale(Float3(2, 2, 2));

    t1->v1 = vp->projectVertex(t1->v1).toFloat3();
    t1->v2 = vp->projectVertex(t1->v2).toFloat3();
    t1->v3 = vp->projectVertex(t1->v3).toFloat3();

        //vp2->mulByTranslation(Float3(0, 0, 20));
//    vp2->mulByRotation(90.0f, Float3(0.0f, 0.0f, 1.0f));
//    vp2->mulByScale(Float3(0.25, 0.25, 0.25));

    t2->v1 = vp2->projectVertex(t2->v1).toFloat3();
    t2->v2 = vp2->projectVertex(t2->v2).toFloat3();
    t2->v3 = vp2->projectVertex(t2->v3).toFloat3();

    std::cout << t1->v1.x << " " << t1->v1.y << " " << t1->v1.z;

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
