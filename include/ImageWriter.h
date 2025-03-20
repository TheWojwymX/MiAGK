#ifndef MIAGK_IMAGEWRITER_H
#define MIAGK_IMAGEWRITER_H

#include "../include/PixelBuffer.h"


class ImageWriter {
private:

public:
    ImageWriter();
    void saveToFile(PixelBuffer* buffer, char* path);

};


#endif //MIAGK_IMAGEWRITER_H
