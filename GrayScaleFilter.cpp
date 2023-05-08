//
// Created by yegor on 11.03.23.
//

#include "GrayScaleFilter.h"

namespace {
double GetNewChannelValue(const double red_value, const double green_value, const double blue_value) {
    static const double RED_CHANNEL_COEF = 0.299;
    static const double GREEN_CHANNEL_COEF = 0.587;
    static const double BLUE_CHANNEL_COEF = 0.114;

    return RED_CHANNEL_COEF * red_value + GREEN_CHANNEL_COEF * green_value + BLUE_CHANNEL_COEF * blue_value;
}
}  // namespace

namespace image_processor {

void GrayScaleFilter::ApplyFilter(Image& image) const {
    std::vector<Image::Channel>& image_channels = image.GetChannels();
    if (image_channels.size() != 3 && image_channels.size() != 1) {
        return;
    }
    if (image_channels.size() == 3) {
        for (size_t y = 0; y < image_channels[0].size(); ++y) {
            for (size_t x = 0; x < image_channels[0][y].size(); ++x) {
                const double new_channel_value =
                    GetNewChannelValue(image_channels[0][y][x], image_channels[1][y][x], image_channels[2][y][x]);
                image_channels[0][y][x] = image_channels[1][y][x] = image_channels[2][y][x] = new_channel_value;
            }
        }
        image_channels.pop_back();
        image_channels.pop_back();
    }
}

}  // namespace image_processor