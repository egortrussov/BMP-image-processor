//
// Created by yegor on 07.03.23.
//

#ifndef CPP_HSE_IMAGE_H
#define CPP_HSE_IMAGE_H

#include <array>
#include <vector>
#include <cstdint>

#pragma pack(push, 1)
struct ImageHeader {
    uint16_t file_type;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t pixel_data_offset;
    uint32_t header_size;
    uint32_t width;
    uint32_t height;
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

class Image {
public:
    using Channel = std::vector<std::vector<double>>;

    struct Resolution {
        size_t height;
        size_t width;

        explicit Resolution(const size_t height, const size_t width);
    };

    struct Pixel {
        double &r;
        double &g;
        double &b;
    };

    struct PixelCoordinates {
        size_t x;
        size_t y;

        explicit PixelCoordinates();
        explicit PixelCoordinates(const size_t x, const size_t y);
    };

    explicit Image(const size_t width, const size_t height);
    explicit Image(const ImageHeader &image_header);

    Resolution GetResolution() const;
    void SetResolution(const Resolution &resolution);

    Pixel GetPixel(const size_t x, const size_t y);
    void SetPixelData(const size_t x, const size_t y, const std::vector<double> &color);

    std::vector<Channel> &GetChannels();

    ImageHeader GetImageHeader() const;

private:
    size_t width_;
    size_t height_;
    std::vector<Channel> channels_;
    ImageHeader image_header_;
};

#endif  // CPP_HSE_IMAGE_H
