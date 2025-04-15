#include <iostream>
#include "../include/PixelBuffer.h"
#include "../include/ImageWriter.h"
#include "../include/mathTypes.h"
#include "../include/Rasterizer.h"
#include "../include/Sphere.h"
#include <cstdlib>
#include <ctime>

int main() {
    // color ARGB
    PixelBuffer* pixelBuffer = new PixelBuffer(0xff0000ff ,800,600);
    ImageWriter* imageWriter = new ImageWriter();
    Rasterizer* rasterizer = new Rasterizer(pixelBuffer);
    VertexProcessor* vp = new VertexProcessor();
    VertexProcessor* vp2 = new VertexProcessor();

    vp->setPerspective(120.0f, 800.0f / 600.0f, 0.1f, 1000.f);
    vp->setLookAt(Float3(0, 0, 0), Float3(0, 0, -1), Float3(0, 1, 0));

    Sphere sphere(1.0f, 8, 8);
    sphere.create();
    vp->mulByTranslation(Float3(0.0f, 0.0f, 10.0f));
    std::vector<Float4> transformedVerts = vp->transformVertices(sphere.vertices);

    for (const auto& index : sphere.indices)
    {
        Float3 v1 = transformedVerts[index.v1].toFloat3();
        Float3 v2 = transformedVerts[index.v2].toFloat3();
        Float3 v3 = transformedVerts[index.v3].toFloat3();

        Float3 c1 = sphere.vertices[index.v1].vertexColor;
        Float3 c2 = sphere.vertices[index.v2].vertexColor;
        Float3 c3 = sphere.vertices[index.v3].vertexColor;

        // You could improve this later by interpolating color based on normal or lighting
        Triangle* t = new Triangle(v1, v2, v3, c1, c2, c3);

        rasterizer->addTriangle(t);
    }






    rasterizer->fillTriangles();

    imageWriter->saveToFile(pixelBuffer, "test.tga");

    // Clean-up
    delete rasterizer;
    delete imageWriter;
    delete pixelBuffer;
}
