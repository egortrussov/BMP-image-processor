//
// Created by yegor on 11.03.23.
//

#include "ChannelWiseFilter.h"

namespace image_processor {

void ChannelWiseFilter::ApplyFilter(Image& image) const {
    for (Image::Channel& channel : image.GetChannels()) {
        FilterImplementation(channel);
    }
}

}  // namespace image_processor
