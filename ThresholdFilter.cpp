//
// Created by yegor on 14.03.23.
//

#include "ThresholdFilter.h"

namespace image_processor {

ThresholdFilter::ThresholdFilter(const double threshold) : threshold_(threshold) {
}

void ThresholdFilter::FilterImplementation(Image::Channel &channel) const {
    for (size_t y = 0; y < channel.size(); ++y) {
        for (size_t x = 0; x < channel[y].size(); ++x) {
            channel[y][x] = (channel[y][x] > threshold_ ? 1 : 0);
        }
    }
}

}  // namespace image_processor