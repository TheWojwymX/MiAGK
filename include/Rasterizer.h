#ifndef MIAGK_RASTERIZER_H
#define MIAGK_RASTERIZER_H

#include <vector>
#include "../include/mathTypes.h"
#include "../include/PixelBuffer.h"
#include "Meshes/Triangle.h"
#include "VertexProcessor.h"


class Rasterizer {
private:
    PixelBuffer* pixelBuffer;
    std::vector<Triangle*> triangles;
    std::vector<Mesh*> meshes;
    unsigned int* textureData = nullptr;
    int texWidth = 128, texHeight = 128;

public:
    Rasterizer(PixelBuffer* pixelBuffer);
    void addTriangle(Triangle* t1);
    void fillTriangles();
    void addMesh(Mesh* mesh);
    void fillMeshes();


};


#endif //MIAGK_RASTERIZER_H
