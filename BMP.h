//
// Created by yegor on 07.03.23.
//
#include <string>

#include "Image.h"

#ifndef CPP_HSE_BMP_H
#define CPP_HSE_BMP_H

class BMP {
public:
    static Image OpenImage(const std::string_view& path);
    static void SaveImage(Image& image, const std::string_view& path);
};

#endif  // CPP_HSE_BMP_H
