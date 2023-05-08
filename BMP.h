//
// Created by yegor on 07.03.23.
//
#include <string>

#include "Image.h"
#include "BMPHeader.h"

#ifndef CPP_HSE_BMP_H
#define CPP_HSE_BMP_H

#include <filesystem>

namespace image_processor {

class BMP final {
public:
    static Image OpenImage(const std::filesystem::path& path);
    static void SaveImage(const Image& image, const std::filesystem::path& path);
};

}  // namespace image_processor
#endif  // CPP_HSE_BMP_H
