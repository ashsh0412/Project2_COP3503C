#include "HelperMethods.h"

int clamp(int value) {
    return std::max(0, std::min(255, value));
}

Image multiply(const Image& top, const Image& bottom) {
    Image result = top;
    for (size_t i = 0; i < result.pixels.size(); ++i) {
        result.pixels[i].r = static_cast<unsigned char>((top.pixels[i].r / 255.0f * bottom.pixels[i].r / 255.0f) * 255 + 0.5f);
        result.pixels[i].g = static_cast<unsigned char>((top.pixels[i].g / 255.0f * bottom.pixels[i].g / 255.0f) * 255 + 0.5f);
        result.pixels[i].b = static_cast<unsigned char>((top.pixels[i].b / 255.0f * bottom.pixels[i].b / 255.0f) * 255 + 0.5f);
    }
    return result;
}

Image subtract(const Image& top, const Image& bottom) {
    Image result = top;
    for (size_t i = 0; i < result.pixels.size(); ++i) {
        result.pixels[i].r = clamp(top.pixels[i].r - bottom.pixels[i].r);
        result.pixels[i].g = clamp(top.pixels[i].g - bottom.pixels[i].g);
        result.pixels[i].b = clamp(top.pixels[i].b - bottom.pixels[i].b);
    }
    return result;
}

Image screen(const Image& bottom, const Image& top) {
    Image result = bottom;
    for (size_t i = 0; i < result.pixels.size(); ++i) {
        result.pixels[i].r = static_cast<unsigned char>((1 - (1 - top.pixels[i].r / 255.0f) * (1 - bottom.pixels[i].r / 255.0f)) * 255 + 0.5f);
        result.pixels[i].g = static_cast<unsigned char>((1 - (1 - top.pixels[i].g / 255.0f) * (1 - bottom.pixels[i].g / 255.0f)) * 255 + 0.5f);
        result.pixels[i].b = static_cast<unsigned char>((1 - (1 - top.pixels[i].b / 255.0f) * (1 - bottom.pixels[i].b / 255.0f)) * 255 + 0.5f);
    }
    return result;
}

Image overlay(const Image& top, const Image& bottom) {
    Image result = top;
    for (size_t i = 0; i < result.pixels.size(); ++i) {
        auto overlayCalc = [](unsigned char a, unsigned char b) {
            float nf1 = a / 255.0f, nf2 = b / 255.0f;
            float out = nf2 <= 0.5f ?
                2 * nf1 * nf2 :
                1 - 2 * (1 - nf1) * (1 - nf2);
            return static_cast<unsigned char>(out * 255 + 0.5f);
        };
        result.pixels[i].r = overlayCalc(top.pixels[i].r, bottom.pixels[i].r);
        result.pixels[i].g = overlayCalc(top.pixels[i].g, bottom.pixels[i].g);
        result.pixels[i].b = overlayCalc(top.pixels[i].b, bottom.pixels[i].b);
    }
    return result;
}

Image addChannel(const Image& img, int value, char channel) {
    Image result = img;
    for (auto& p : result.pixels) {
        if (channel == 'r') p.r = clamp(p.r + value);
        if (channel == 'g') p.g = clamp(p.g + value);
        if (channel == 'b') p.b = clamp(p.b + value);
    }
    return result;
}

Image scaleChannel(const Image& img, float factor, char channel) {
    Image result = img;
    for (auto& p : result.pixels) {
        if (channel == 'r') p.r = clamp(static_cast<int>(p.r * factor));
        if (channel == 'g') p.g = clamp(static_cast<int>(p.g * factor));
        if (channel == 'b') p.b = clamp(static_cast<int>(p.b * factor));
    }
    return result;
}

Image onlyChannel(const Image& img, char channel) {
    Image result = img;
    for (auto& p : result.pixels) {
        unsigned char val = (channel == 'r') ? p.r : (channel == 'g' ? p.g : p.b);
        p.r = p.g = p.b = val;
    }
    return result;
}

Image combineChannels(const Image& r, const Image& g, const Image& b) {
    Image result = r;
    for (size_t i = 0; i < result.pixels.size(); ++i) {
        result.pixels[i].r = r.pixels[i].r;
        result.pixels[i].g = g.pixels[i].g;
        result.pixels[i].b = b.pixels[i].b;
    }
    return result;
}

Image flip180(const Image& img) {
    Image result = img;
    std::reverse(result.pixels.begin(), result.pixels.end());
    return result;
}