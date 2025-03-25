#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <fstream>

struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

struct Pixel {
    unsigned char b, g, r;
};

class Image {
public:
    Header header;
    std::vector<Pixel> pixels;

    Image() = default;
    Image(const std::string& filename);

    bool read(const std::string& filename);
    bool write(const std::string& filename) const;

    int getWidth() const;
    int getHeight() const;
    Pixel& getPixel(int x, int y);
    const Pixel& getPixel(int x, int y) const;
};

#endif