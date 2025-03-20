cmake_minimum_required(VERSION 3.28)
project(MiAGK)

set(CMAKE_CXX_STANDARD 17)

add_executable(MiAGK src/main.cpp
        src/PixelBuffer.cpp
        include/PixelBuffer.h
        src/Rasterizer.cpp
        include/Rasterizer.h
        src/ImageWriter.cpp
        include/ImageWriter.h)
