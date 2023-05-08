//
// Created by yegor on 11.03.23.
//

#include "CropFilter.h"

namespace image_processor {

CropFilter::CropFilter(const size_t height, const size_t width) : height_(height), width_(width) {
}

void CropFilter::FilterImplementation(Image::Channel& channel) const {
    const size_t new_height = std::min(channel.size(), height_);
    const size_t new_width = std::min(channel[0].size(), width_);
    channel.resize(new_height);
    for (auto& row : channel) {
        row.resize(new_width);
    }
}

}  // namespace image_processor
