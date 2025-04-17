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

    Sphere* sphere = new Sphere(1.0f, 8, 8);
    rasterizer->addMesh(sphere);
    sphere->vertexProcessor->setTransform(Float3(1.0f, 1.0f, 1.0f), 0, Float3(0.0f, 0.0f, 0.0f), Float3(0.0f, -5.0f, 20.0f));


    Cone* cone = new Cone(1.0f, 16, 16);
    rasterizer->addMesh(cone);
    cone->vertexProcessor->setTransform(Float3(1.0f, 1.0f, 2.0f), 70, Float3(1.0f, 0.0f, 0.0f), Float3(-5.0f, 0.0f, 20.0f));


    Cylinder* cylinder = new Cylinder(1.0f, 1.0f, 16, 1);
    rasterizer->addMesh(cylinder);
    cylinder->vertexProcessor->setTransform(Float3(1.0f, 1.0f, 2.0f), 60, Float3(1.0f, 1.0f, 0.0f), Float3(5.0f, 0.0f, 20.0f));

    Torus* torus = new Torus(1.0f, 0.3f, 8, 8);
    rasterizer->addMesh(torus);
    torus->vertexProcessor->setTransform(Float3(1.0f, 1.0f, 1.0f), 0, Float3(0.0f, 0.0f, 0.0f), Float3(0.0f, 0.0f, 10.0f));


    rasterizer->fillMeshes();
    rasterizer->fillTriangles();








    rasterizer->fillTriangles();

    imageWriter->saveToFile(pixelBuffer, "test.tga");

    // Clean-up
    delete rasterizer;
    delete imageWriter;
    delete pixelBuffer;
}
