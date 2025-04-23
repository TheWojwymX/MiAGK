cmake_minimum_required(VERSION 3.28)
project(MiAGK)

set(CMAKE_CXX_STANDARD 17)

add_executable(MiAGK src/main.cpp
        src/PixelBuffer.cpp
        include/PixelBuffer.h
        src/Rasterizer.cpp
        include/Rasterizer.h
        src/ImageWriter.cpp
        include/ImageWriter.h
        include/mathTypes.h
        src/Meshes/Triangle.cpp
        include/Meshes/Triangle.h
        src/VertexProcessor.cpp
        include/VertexProcessor.h
        src/Meshes/Mesh.cpp
        include/Meshes/Mesh.h
        src/Meshes/Sphere.cpp
        include/Meshes/Sphere.h
        src/Meshes/Mesh.cpp
        src/Meshes/Cone.cpp
        include/Meshes/Cone.h
        src/Meshes/Cylinder.cpp
        include/Meshes/Cylinder.h
        src/Meshes/Torus.cpp
        include/Meshes/Torus.h
        src/Light/Light.cpp
        include/Light/Light.h
        src/Light/DirectionalLight.cpp
        include/Light/DirectionalLight.h
        src/Light/PointLight.cpp
        include/Light/PointLight.h
        src/Light/Spotlight.cpp
        include/Light/Spotlight.h
)
