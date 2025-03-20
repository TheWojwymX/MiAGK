#ifndef MIAGK_PIXELBUFFER_H
#define MIAGK_PIXELBUFFER_H
class PixelBuffer {
private:
    int height;
    int width;
    unsigned int* buffer;


public:
    PixelBuffer(unsigned int color, int height, int width);
    void clearBuffer(unsigned int color);
    void setSize(int height, int width);
    int getHeight() const;
    void setHeight(int height);
    int getWidth() const;
    void setWidth(int width);
    unsigned int *getBuffer() const;
    void setBuffer(unsigned int *buffer);

};


#endif //MIAGK_PIXELBUFFER_H
