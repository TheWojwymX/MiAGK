#include "../include/ImageWriter.h"
#include <fstream>

ImageWriter::ImageWriter()
{

}

void ImageWriter::saveToFile(PixelBuffer* buffer, char *path)
{
    int height = buffer->getHeight();
    int width = buffer->getWidth();
    unsigned int* pixels = buffer->getPixelBuffer();

    std::ofstream file(path, std::ios::binary);

    uint8_t tgaHeader[18] = {
            0, 0, 2,   // Brak ID, brak mapy kolorów, typ obrazu 2 (Truecolor, nieskompresowany)
            0, 0, 0, 0, 0, // Mapa kolorów
            0, 0,  // X-origin (0)
            0, 0,  // Y-origin (0)
            (uint8_t)(width & 0xFF), (uint8_t)((width >> 8) & 0xFF),   // Szerokość
            (uint8_t)(height & 0xFF), (uint8_t)((height >> 8) & 0xFF), // Wysokość
            32,  // 32-bitowe ARGB
            8    // 8 bitów alfa
    };

    file.write((char*)tgaHeader, sizeof(tgaHeader));

    for (int i = 0; i < width * height; i++) {
        uint32_t pixel = pixels[i];
        uint8_t bgra[4] = {
                (uint8_t)(pixel & 0xFF),        // B
                (uint8_t)((pixel >> 8) & 0xFF), // G
                (uint8_t)((pixel >> 16) & 0xFF),// R
                (uint8_t)((pixel >> 24) & 0xFF) // A
        };
        file.write((char*)bgra, 4);
    }

    file.close();
}