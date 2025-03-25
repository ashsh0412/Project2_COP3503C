#ifndef HELPERMETHODS_H
#define HELPERMETHODS_H

#include "Image.h"

Image multiply(const Image& top, const Image& bottom);
Image subtract(const Image& top, const Image& bottom);
Image screen(const Image& bottom, const Image& top);
Image overlay(const Image& top, const Image& bottom);

Image addChannel(const Image& img, int value, char channel);
Image scaleChannel(const Image& img, float factor, char channel);
Image onlyChannel(const Image& img, char channel);
Image combineChannels(const Image& r, const Image& g, const Image& b);
Image flip180(const Image& img);

int clamp(int value);

#endif