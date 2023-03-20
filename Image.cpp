//
// Created by yegor on 07.03.23.
//

#include "Image.h"
#include <iostream>

Image::Resolution::Resolution(const size_t height, const size_t width) : height(height), width(width) {
}

Image::PixelCoordinates::PixelCoordinates() : x(0), y(0) {
}

Image::PixelCoordinates::PixelCoordinates(const size_t x, const size_t y) : x(x), y(y) {
}

Image::Image(const size_t width, const size_t height) : width_(width), height_(height) {
    channels_.assign(3, Channel(height_, std::vector<double>(width_, 0)));
}

Image::Image(const ImageHeader& image_header)
    : width_(image_header.width), height_(image_header.height), image_header_(image_header) {
    channels_.assign(3, Channel(height_, std::vector<double>(width_, 0)));
}

Image::Resolution Image::GetResolution() const {
    return Resolution(height_, width_);
}

void Image::SetResolution(const Resolution& resolution) {
    height_ = resolution.height;
    width_ = resolution.width;
    image_header_.width = width_;
    image_header_.height = height_;
    image_header_.file_size = width_ * height_ * image_header_.bits_per_pixel + image_header_.pixel_data_offset;
}

ImageHeader Image::GetImageHeader() const {
    return image_header_;
}

Image::Pixel Image::GetPixel(const size_t x, const size_t y) {
    if (channels_.size() == 1) {
        return Pixel{.r = channels_[0][y][x], .g = channels_[0][y][x], .b = channels_[0][y][x]};
    }
    return Pixel{.r = channels_[0][y][x], .g = channels_[1][y][x], .b = channels_[2][y][x]};
}

void Image::SetPixelData(const size_t x, const size_t y, const std::vector<double>& color) {
    for (size_t channel_index = 0; channel_index < channels_.size(); ++channel_index) {
        channels_[channel_index][y][x] = color[channel_index];
    }
}

std::vector<Image::Channel>& Image::GetChannels() {
    return channels_;
}