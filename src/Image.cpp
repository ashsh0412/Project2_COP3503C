#include "Image.h"
#include <iostream>

Image::Image(const std::string& filename) {
    read(filename);
}

bool Image::read(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) return false;

    in.read(&header.idLength, 1);
    in.read(&header.colorMapType, 1);
    in.read(&header.dataTypeCode, 1);
    in.read(reinterpret_cast<char*>(&header.colorMapOrigin), 2);
    in.read(reinterpret_cast<char*>(&header.colorMapLength), 2);
    in.read(&header.colorMapDepth, 1);
    in.read(reinterpret_cast<char*>(&header.xOrigin), 2);
    in.read(reinterpret_cast<char*>(&header.yOrigin), 2);
    in.read(reinterpret_cast<char*>(&header.width), 2);
    in.read(reinterpret_cast<char*>(&header.height), 2);
    in.read(&header.bitsPerPixel, 1);
    in.read(&header.imageDescriptor, 1);

    int size = header.width * header.height;
    pixels.resize(size);
    in.read(reinterpret_cast<char*>(pixels.data()), size * sizeof(Pixel));

    in.close();
    return true;
}

bool Image::write(const std::string& filename) const {
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        std::cerr << "❌ Failed to open file for writing: " << filename << std::endl;
        return false;
    }

    // header 쓰기
    out.write(&header.idLength, 1);
    out.write(&header.colorMapType, 1);
    out.write(&header.dataTypeCode, 1);
    out.write(reinterpret_cast<const char*>(&header.colorMapOrigin), 2);
    out.write(reinterpret_cast<const char*>(&header.colorMapLength), 2);
    out.write(&header.colorMapDepth, 1);
    out.write(reinterpret_cast<const char*>(&header.xOrigin), 2);
    out.write(reinterpret_cast<const char*>(&header.yOrigin), 2);
    out.write(reinterpret_cast<const char*>(&header.width), 2);
    out.write(reinterpret_cast<const char*>(&header.height), 2);
    out.write(&header.bitsPerPixel, 1);
    out.write(&header.imageDescriptor, 1);

    // 픽셀 데이터 쓰기
    out.write(reinterpret_cast<const char*>(pixels.data()), pixels.size() * sizeof(Pixel));

    out.close();
    return true;
}

int Image::getWidth() const { return header.width; }
int Image::getHeight() const { return header.height; }
Pixel& Image::getPixel(int x, int y) { return pixels[y * header.width + x]; }
const Pixel& Image::getPixel(int x, int y) const { return pixels[y * header.width + x]; }