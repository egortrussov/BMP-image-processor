//
// Created by yegor on 07.03.23.
//

#include "BMP.h"

#include <fstream>
#include <iostream>
#include <cmath>

namespace {
void ReadDataFromStream(std::ifstream& stream, unsigned char (&data_container)[], const std::streamsize data_size) {
    stream.read(reinterpret_cast<char*>(data_container), data_size);
}

void ReadFileHeader(std::ifstream& stream, ImageHeader& header) {
    stream.read(reinterpret_cast<char*>(&header), sizeof(header));
}

std::streamsize GetDataPaddingAmount(const size_t bitmap_width) {
    return static_cast<std::streamsize>((4 - ((bitmap_width)*3) % 4) % 4);
}

std::vector<double> ConvertPixelData(const unsigned char pixel_color[]) {
    static const double MAX_CHANNEL_VALUE = 255;
    return std::vector<double>({static_cast<double>(pixel_color[2]) / MAX_CHANNEL_VALUE,
                                static_cast<double>(pixel_color[1]) / MAX_CHANNEL_VALUE,
                                static_cast<double>(pixel_color[0]) / MAX_CHANNEL_VALUE});
}

unsigned char GetWholeChannelValue(const double value) {
    static const int MAX_CHANNEL_VALUE = 255;
    return static_cast<unsigned char>(floor(value * MAX_CHANNEL_VALUE));
}

void ReadImagePixelData(std::ifstream& stream, Image& image) {
    const auto [height, width] = image.GetResolution();
    const std::streamsize padding_amount = GetDataPaddingAmount(width);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char pixel_color[3];
            ReadDataFromStream(stream, pixel_color, 3);
            image.SetPixelData(x, height - y - 1, ConvertPixelData(pixel_color));
        }
        stream.ignore(padding_amount);
    }
}

void WriteImageHeaderToFile(std::ofstream& stream, ImageHeader image_header) {
    stream.write(reinterpret_cast<char*>(&image_header), sizeof(image_header));
}

void WritePaddingSymbols(std::ofstream& stream, const std::streamsize padding_amount) {
    if (padding_amount == 0) {
        return;
    }
    unsigned char padding_symbols[padding_amount];
    stream.write(reinterpret_cast<char*>(padding_symbols), padding_amount);
}

void WritePixelDataToFile(std::ofstream& stream, unsigned char pixel_data[]) {
    stream.write(reinterpret_cast<char*>(pixel_data), 3);
}
}  // namespace

Image BMP::OpenImage(const std::string_view& path) {
    std::ifstream stream;
    stream.open(std::string(path), std::ios_base::binary);
    if (!stream.is_open()) {
        throw std::invalid_argument("Could not open the file");
    }

    ImageHeader image_header;
    ReadFileHeader(stream, image_header);
    Image image(image_header);
    ReadImagePixelData(stream, image);

    stream.close();

    std::cout << "Successfully read the file\n";

    return image;
}

void BMP::SaveImage(Image& image, const std::string_view& path) {
    std::ofstream stream(std::string(path), std::ios_base::binary);
    if (!stream.is_open()) {
        throw std::invalid_argument("Unable to write to the file");
    }
    WriteImageHeaderToFile(stream, image.GetImageHeader());
    const auto [image_height, image_width] = image.GetResolution();
    const std::streamsize padding_amount = GetDataPaddingAmount(image_width);
    for (size_t row = 0; row < image_height; ++row) {
        for (size_t col = 0; col < image_width; ++col) {
            Image::Pixel pixel = image.GetPixel(col, image_height - row - 1);
            unsigned char pixel_data[] = {GetWholeChannelValue(pixel.b), GetWholeChannelValue(pixel.g),
                                          GetWholeChannelValue(pixel.r)};
            WritePixelDataToFile(stream, pixel_data);
        }
        WritePaddingSymbols(stream, padding_amount);
    }
    std::cout << "Successfully saved the image\n";
}
