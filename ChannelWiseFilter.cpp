//
// Created by yegor on 11.03.23.
//

#include "ChannelWiseFilter.h"

void ChannelWiseFilter::ApplyFilter(Image& image) const {
    for (Image::Channel& channel : image.GetChannels()) {
        FilterImplementation(channel);
    }
}
