//
// Created by yegor on 11.03.23.
//

#include "CropFilter.h"
#include <iostream>

CropFilter::CropFilter(const size_t height, const size_t width) : height_(height), width_(width) {
}

void CropFilter::ApplyFilter(Image& image) const {
    std::vector<Image::Channel>& channels = image.GetChannels();
    const auto [old_height, old_width] = image.GetResolution();
    const size_t new_height = std::min(old_height, height_);
    const size_t new_width = std::min(old_width, width_);
    for (Image::Channel& channel : channels) {
        channel.resize(new_height);
        for (auto& row : channel) {
            row.resize(new_width);
        }
    }
    image.SetResolution(Image::Resolution(new_height, new_width));
}
