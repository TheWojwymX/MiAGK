#include <iostream>
#include "../include/PixelBuffer.h"
#include "../include/ImageWriter.h"
#include "../include/mathTypes.h"
#include "../include/Rasterizer.h"
#include "../include/Meshes/Sphere.h"
#include "../include/Meshes/Cone.h"
#include "../include/Meshes/Cylinder.h"
#include "../include/Meshes/Torus.h"
#include <cstdlib>
#include <ctime>

int main() {
    // color ARGB
    PixelBuffer* pixelBuffer = new PixelBuffer(0xff0000ff ,800,600);
    ImageWriter* imageWriter = new ImageWriter();
    Rasterizer* rasterizer = new Rasterizer(pixelBuffer);
    VertexProcessor* vp = new VertexProcessor();

    vp->setPerspective(120.0f, 800.0f / 600.0f, 0.1f, 1000.f);
    vp->setLookAt(Float3(0, 0, 0), Float3(0, 0, -1), Float3(0, 1, 0));
    rasterizer->vertexProcessor = vp;

//    Sphere* sphere = new Sphere(1.0f, 8, 8);
//    rasterizer->addMesh(sphere);

//    Cone* cone = new Cone(1.0f, 16, 16);
//    rasterizer->addMesh(cone);

//    Cylinder* cylinder = new Cylinder(1.0f, 1.0f, 16, 1);
//    rasterizer->addMesh(cylinder);

    Torus* torus = new Torus(1.0f, 0.3f, 8, 8);
    rasterizer->addMesh(torus);

    vp->setTransform(Float3(1.0f, 1.0f, 1.0f), 0, Float3(0.0f, 0.0f, 0.0f), Float3(0.0f, 0.0f, 10.0f));
    rasterizer->fillMeshes();
    rasterizer->fillTriangles();








    rasterizer->fillTriangles();

    imageWriter->saveToFile(pixelBuffer, "test.tga");

    // Clean-up
    delete rasterizer;
    delete imageWriter;
    delete pixelBuffer;
}
