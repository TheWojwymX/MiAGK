#ifndef MIAGK_IMAGEWRITER_H
#define MIAGK_IMAGEWRITER_H

#include "../include/PixelBuffer.h"


class ImageWriter {
private:

public:
    ImageWriter();
    void saveToFile(PixelBuffer* buffer, char* path);
    bool loadTGA(const char* filename, unsigned int*& data, int& width, int& height);

};


#endif //MIAGK_IMAGEWRITER_H
