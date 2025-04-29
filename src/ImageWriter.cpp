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

bool ImageWriter::loadTGA(const char* filename, unsigned int*& data, int& width, int& height) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;

    uint8_t header[18];
    file.read((char*)header, 18);

    width = header[12] + (header[13] << 8);
    height = header[14] + (header[15] << 8);
    int bpp = header[16];

    if (bpp != 32) return false;

    int size = width * height;
    uint8_t* temp = new uint8_t[size * 4];
    file.read((char*)temp, size * 4);

    data = new unsigned int[size];
    for (int i = 0; i < size; ++i) {
        uint8_t b = temp[i * 4 + 0];
        uint8_t g = temp[i * 4 + 1];
        uint8_t r = temp[i * 4 + 2];
        uint8_t a = temp[i * 4 + 3];
        data[i] = (a << 24) | (r << 16) | (g << 8) | b;
    }

    delete[] temp;
    file.close();
    return true;
}