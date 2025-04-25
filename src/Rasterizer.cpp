#include <algorithm>
#include <iostream>
#include "../include/Rasterizer.h"

Rasterizer::Rasterizer(PixelBuffer* pixelBuffer)
{
    this->pixelBuffer = pixelBuffer;
}

void Rasterizer::addMesh(Mesh* mesh)
{
    meshes.push_back(mesh);
}

void Rasterizer::fillMeshes()
{
    for (Mesh* mesh : meshes)
    {
        mesh->create();
        // Get transformed positions
        std::vector<Float4> transformed = mesh->vertexProcessor->transformVertices(mesh->vertices);

        for (const auto& index : mesh->indices)
        {
            Float3 v1 = transformed[index.v1].toFloat3();
            Float3 v2 = transformed[index.v2].toFloat3();
            Float3 v3 = transformed[index.v3].toFloat3();

            Float3 c1 = mesh->vertices[index.v1].vertexColor;
            Float3 c2 = mesh->vertices[index.v2].vertexColor;
            Float3 c3 = mesh->vertices[index.v3].vertexColor;

            Float3 normal1 = mesh->vertexProcessor->transformNormal(mesh->vertices[index.v1].normal);
            Float3 normal2 = mesh->vertexProcessor->transformNormal(mesh->vertices[index.v2].normal);
            Float3 normal3 = mesh->vertexProcessor->transformNormal(mesh->vertices[index.v3].normal);

            Float3 world1 = (mesh->vertexProcessor->obj2world * Float4(mesh->vertices[index.v1].position, 1.0f)).toFloat3();
            Float3 world2 = (mesh->vertexProcessor->obj2world * Float4(mesh->vertices[index.v2].position, 1.0f)).toFloat3();
            Float3 world3 = (mesh->vertexProcessor->obj2world * Float4(mesh->vertices[index.v3].position, 1.0f)).toFloat3();

            Triangle* t = new Triangle(v1, v2, v3, c1, c2, c3);
            t->vp = mesh->vertexProcessor;
            t->n1 = normal1;
            t->n2 = normal2;
            t->n3 = normal3;
            t->w1 = world1;
            t->w2 = world2;
            t->w3 = world3;
            addTriangle(t);
        }
    }
}

void Rasterizer::fillTriangles()
{
    unsigned int* buffer = pixelBuffer->getPixelBuffer();
    float* zBuffer = pixelBuffer->getZBuffer();
    int width = pixelBuffer->getWidth();
    int height = pixelBuffer->getHeight();

    for(int i = 0; i < triangles.size(); i++)
    {
        Triangle* tri = triangles[i];

        int v1x = (triangles[i]->v1.x + 1) * width * 0.5f;
        int v1y = (triangles[i]->v1.y + 1) * height * 0.5f;
        int v1z = (triangles[i]->v1.z + 1) * width * 0.5f;

        int v2x = (triangles[i]->v2.x + 1) * width * 0.5f;
        int v2y = (triangles[i]->v2.y + 1) * height * 0.5f;
        int v2z = (triangles[i]->v2.z + 1) * width * 0.5f;

        int v3x = (triangles[i]->v3.x + 1) * width * 0.5f;
        int v3y = (triangles[i]->v3.y + 1) * height * 0.5f;
        int v3z = (triangles[i]->v3.z + 1) * width * 0.5f;

        int dx12 = v1x - v2x;
        int dx23 = v2x - v3x;
        int dx31 = v3x - v1x;

        int dy12 = v1y - v2y;
        int dy23 = v2y - v3y;
        int dy31 = v3y - v1y;

        int maxx = std::max({v1x, v2x, v3x});
        int minx = std::min({v1x, v2x, v3x});
        int maxy = std::max({v1y, v2y, v3y});
        int miny = std::min({v1y, v2y, v3y});

        minx = std::max(minx, 0);
        maxx = std::min(maxx, width-1);
        miny = std::max(miny, 0);
        maxy = std::min(maxy, height-1);

        bool t1 = (dy12 <  0 || (dy12 == 0 && dx12 > 0));
        bool t2 = (dy23 < 0 || (dy23 == 0 && dx23 > 0));
        bool t3 = (dy31 < 0 || (dy31 == 0 && dx31 >0));

        for(int x = minx; x < maxx; x++)
        {
            for (int y = miny; y < maxy; y++)
            {
                if (( dx12 * (y - v1y) - dy12 * (x - v1x) ) >= (t1 ? 0 : 1) // >= but shifted by one
                    && ( dx23 * (y - v2y) - dy23 * (x - v2x) ) >= (t2 ? 0 : 1)
                    && ( dx31 * (y - v3y) - dy31 * (x - v3x) ) >= (t3 ? 0 : 1))
                {
                    float k1 = float ((dy23 * (x - v3x)) + (-dx23 * (y - v3y))) / ( dy23 * (-dx31) + (-dx23) * (-dy31) );
                    float k2 = float ((dy31 * (x - v3x)) + (-dx31 * (y - v3y))) / ( dy31 * dx23 + (-dx31) * dy23 );
                    float k3 = 1 - k1 - k2;

                    float depth = k1 * v1z + k2 * v2z + k3 * v3z;
                    if(depth < zBuffer[x + y * width]) continue;

                    Float3 color(0,0,0);

                    if(usePhongShading == false)
                    {
                        color = triangles[i]->c1 * k1 + triangles[i]->c2 * k2 + triangles[i]->c3 * k3;
                    }
                    else
                    {
                        Float3 interpolatedNormal = triangles[i]->n1 * k1 + triangles[i]->n2 * k2 + triangles[i]->n3 * k3;
                        interpolatedNormal.normalize();

                        Float3 interpolatedWorldPos = triangles[i]->w1 * k1 + triangles[i]->w2 * k2 + triangles[i]->w3 * k3;

                        std::vector<Light*> lights = triangles[i]->vp->lights;

                        color = Float3(0, 0, 0);
                        for (Light* light : lights)
                        {
                            color = color + light->calculate(*triangles[i]->vp, interpolatedWorldPos, interpolatedNormal)
                                    * (triangles[i]->c1 * k1 + triangles[i]->c2 * k2 + triangles[i]->c3 * k3);
                        }
                    }

                    color.r = std::clamp(color.r, 0.0f, 1.0f);
                    color.g = std::clamp(color.g, 0.0f, 1.0f);
                    color.b = std::clamp(color.b, 0.0f, 1.0f);

                    unsigned int hexColor = (0xFF << 24) | ((unsigned char)(color.r * 255.0f) << 16)
                            | ((unsigned char)(color.g * 255.0f) << 8) | (unsigned char)(color.b * 255.0f) ;
                    buffer[x + y * width] = hexColor;
                    zBuffer[x + y * width] = depth;
                }
            }
        }
    }
}

void Rasterizer::addTriangle(Triangle* t1)
{
    triangles.push_back(t1);
}

