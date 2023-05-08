//
// Created by yegor on 21.03.23.
//

#ifndef CPP_HSE_BMPHEADER_H
#define CPP_HSE_BMPHEADER_H

#include <cstdlib>
#include <cstdint>

namespace image_processor {

static const size_t COLOR_BITMAP_SIZE = 3;
static const int32_t MAX_CHANNEL_VALUE = 255;
static const uint16_t FILE_TYPE = 0x4D42;
static const uint32_t FILE_HEADER_SIZE = 14;
static const uint32_t INFO_HEADER_SIZE = 40;
static const uint16_t PLANES_COUNT = 1;
static const uint16_t BITS_PER_PIXEL = 24;
static const uint32_t X_PIXELS_PER_METER = 2835;
static const uint32_t Y_PIXELS_PER_METER = 2835;
static const uint32_t PALETTE_COLORS = 0;
static const uint32_t IMPORTANT_COLORS = 0;

#pragma pack(push, 1)
struct BMPImageHeader {
    uint16_t file_type;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t pixel_data_offset;
    uint32_t header_size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t image_size;
    uint32_t x_pixels_per_meter;
    uint32_t y_pixels_per_meter;
    uint32_t palette_colors;
    uint32_t important_colors;
};
#pragma pack(pop)

}  // namespace image_processor

#endif  // CPP_HSE_BMPHEADER_H
