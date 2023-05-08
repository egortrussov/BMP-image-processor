//
// Created by yegor on 07.03.23.
//

#include "BMP.h"

#include <fstream>
#include <cmath>

namespace image_processor {

namespace {

BMPImageHeader GenerateImageHeader(const size_t image_width, const size_t image_height, const size_t padding_amount) {
    BMPImageHeader header;
    header.file_type = FILE_TYPE;
    header.file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + image_width * image_height * COLOR_BITMAP_SIZE +
                       padding_amount * image_height;
    header.reserved1 = 0;
    header.reserved2 = 0;
    header.pixel_data_offset = INFO_HEADER_SIZE + FILE_HEADER_SIZE;
    header.header_size = INFO_HEADER_SIZE;
    header.width = static_cast<int32_t>(image_width);
    header.height = static_cast<int32_t>(image_height);
    header.planes = PLANES_COUNT;
    header.bits_per_pixel = BITS_PER_PIXEL;
    header.compression = 0;
    header.image_size = 0;
    header.x_pixels_per_meter = 0;
    header.y_pixels_per_meter = 0;
    header.palette_colors = PALETTE_COLORS;
    header.important_colors = IMPORTANT_COLORS;

    return header;
}

void ValidateImageHeader(const BMPImageHeader& header) {
    if (header.header_size != INFO_HEADER_SIZE) {
        throw std::invalid_argument("Error in image header: header_size is invalid: " +
                                    std::to_string(header.header_size));
    }
    if (header.width < 0) {
        throw std::invalid_argument("Processor does not support images with negative width");
    }
    if (header.planes != PLANES_COUNT) {
        throw std::invalid_argument("Processor does not support images with planes number not equal to 1");
    }
    if (header.bits_per_pixel != BITS_PER_PIXEL) {
        throw std::invalid_argument("Processor only supports 24-bit images");
    }
}

template <typename T>
void ReadDataFromStream(std::ifstream& stream, T& data_container) {
    stream.read(reinterpret_cast<char*>(&data_container), sizeof(data_container));
}

std::streamsize GetDataPaddingAmount(const size_t bitmap_width) {
    static const size_t INTENDED_COLOR_BITMAP_SIZE = 4;

    const size_t current_bitmap_width = bitmap_width * COLOR_BITMAP_SIZE;
    const size_t remaining_bitmap_size = INTENDED_COLOR_BITMAP_SIZE - current_bitmap_width % INTENDED_COLOR_BITMAP_SIZE;
    return static_cast<std::streamsize>(remaining_bitmap_size % INTENDED_COLOR_BITMAP_SIZE);
}

double GetNormalizedChannelValue(const int32_t value) {
    return static_cast<double>(value) / MAX_CHANNEL_VALUE;
}
char8_t GetWholeChannelValue(const double value) {
    return static_cast<unsigned char>(floor(value * MAX_CHANNEL_VALUE));
}

void ReadImagePixelData(std::ifstream& stream, Image& image, bool is_height_negative = false) {
    const auto [height, width] = image.GetResolution();
    const std::streamsize padding_amount = GetDataPaddingAmount(width);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            char8_t pixel_color[COLOR_BITMAP_SIZE];
            ReadDataFromStream<char8_t[COLOR_BITMAP_SIZE]>(stream, pixel_color);
            const double red = GetNormalizedChannelValue(pixel_color[2]);
            const double green = GetNormalizedChannelValue(pixel_color[1]);
            const double blue = GetNormalizedChannelValue(pixel_color[0]);
            image.SetPixelData(x, (is_height_negative ? y : height - y - 1), {red, green, blue});
        }
        stream.ignore(padding_amount);
    }
}

void WriteImageHeaderToFile(std::ofstream& stream, BMPImageHeader image_header) {
    stream.write(reinterpret_cast<char*>(&image_header), sizeof(image_header));
}

void WritePaddingSymbols(std::ofstream& stream, const std::streamsize padding_amount) {
    if (padding_amount == 0) {
        return;
    }
    char8_t padding_symbols[padding_amount];
    stream.write(reinterpret_cast<char*>(padding_symbols), padding_amount);
}

void WritePixelDataToFile(std::ofstream& stream, const Image::Pixel& pixel) {
    char8_t pixel_data[] = {GetWholeChannelValue(pixel.b), GetWholeChannelValue(pixel.g),
                            GetWholeChannelValue(pixel.r)};
    stream.write(reinterpret_cast<char*>(pixel_data), COLOR_BITMAP_SIZE);
}
}  // namespace

Image BMP::OpenImage(const std::filesystem::path& path) {
    std::ifstream stream;
    stream.open(path, std::ios_base::binary);
    if (!stream.is_open()) {
        throw std::invalid_argument("Could not open the provided file");
    }

    BMPImageHeader image_header;
    ReadDataFromStream<BMPImageHeader>(stream, image_header);
    ValidateImageHeader(image_header);
    bool is_height_negative = (image_header.height < 0);
    Image image(image_header.width, abs(image_header.height));
    ReadImagePixelData(stream, image, is_height_negative);

    return image;
}

void BMP::SaveImage(const Image& image, const std::filesystem::path& path) {
    std::ofstream stream(path, std::ios_base::binary);
    if (!stream.is_open()) {
        throw std::invalid_argument("Unable to write to the output file");
    }
    const auto [image_height, image_width] = image.GetResolution();
    const std::streamsize padding_amount = GetDataPaddingAmount(image_width);
    BMPImageHeader header = GenerateImageHeader(image_width, image_height, padding_amount);
    WriteImageHeaderToFile(stream, header);

    for (size_t row = 0; row < image_height; ++row) {
        for (size_t col = 0; col < image_width; ++col) {
            const Image::Pixel pixel = image.GetPixel(col, image_height - row - 1);
            WritePixelDataToFile(stream, pixel);
        }
        WritePaddingSymbols(stream, padding_amount);
    }
}

}  // namespace image_processor