#ifndef MIAGK_PIXELBUFFER_H
#define MIAGK_PIXELBUFFER_H
class PixelBuffer {
private:
    int height;
    int width;
    unsigned int* pixelBuffer;
    float* zBuffer;

public:
    PixelBuffer(unsigned int color, int height, int width);
    void clearPixelBuffer(unsigned int color);
    void setSize(int height, int width);
    int getHeight() const;
    void setHeight(int height);
    int getWidth() const;
    void setWidth(int width);
    unsigned int *getPixelBuffer() const;
    void setPixelBuffer(unsigned int *buffer);
    float *getZBuffer() const;
    void setZBuffer(float *zBuffer);

};


#endif //MIAGK_PIXELBUFFER_H
