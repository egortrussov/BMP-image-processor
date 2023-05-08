//
// Created by yegor on 07.03.23.
//

#include "Image.h"

namespace {
const size_t DEFAULT_CHANNELS_NUMBER = 3;
}

namespace image_processor {

Image::Resolution::Resolution(const size_t height, const size_t width) : height(height), width(width) {
}

Image::PixelCoordinates::PixelCoordinates() : x(0), y(0) {
}

Image::PixelCoordinates::PixelCoordinates(const size_t x, const size_t y) : x(x), y(y) {
}

Image::Image(const size_t width, const size_t height) {
    channels_.assign(DEFAULT_CHANNELS_NUMBER, Channel(height, std::vector<double>(width, 0)));
}

Image::Resolution Image::GetResolution() const {
    if (channels_.empty() || channels_[0].empty()) {
        return Resolution(0, 0);
    }
    return Resolution(channels_[0].size(), channels_[0][0].size());
}

const Image::Pixel Image::GetPixel(const size_t x, const size_t y) const {
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

}  // namespace image_processor