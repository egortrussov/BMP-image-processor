//
// Created by yegor on 11.03.23.
//

#include "NegativeFilter.h"

void NegativeFilter::FilterImplementation(Image::Channel &channel) const {
    for (size_t y = 0; y < channel.size(); ++y) {
        for (size_t x = 0; x < channel[y].size(); ++x) {
            channel[y][x] = 1 - channel[y][x];
        }
    }
}