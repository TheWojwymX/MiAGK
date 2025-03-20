#include <iostream>
#include "../include/PixelBuffer.h"
#include "../include/ImageWriter.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    // color ARGB
    PixelBuffer* pixelBuffer = new PixelBuffer(0xff00ffff ,256,256);
    ImageWriter* imageWriter = new ImageWriter();
    imageWriter->saveToFile(pixelBuffer, "test.tga");
}
