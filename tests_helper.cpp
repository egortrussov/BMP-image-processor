//
// Created by yegor on 25.03.23.
//

#ifndef TESTS_HELPER_CPP
#define TESTS_HELPER_CPP

#include "Image.h"
#include "test_images_data.h"

#include <cmath>
#include <vector>

namespace {
double CalculateDifferenceBetweenPixels(const image_processor::Image::Pixel& pixel1,
                                        const image_processor::Image::Pixel& pixel2) {
    static const double MAX_CHANNEL_VALUE = 255;

    const double r1 = std::floor(pixel1.r * MAX_CHANNEL_VALUE);
    const double r2 = std::floor(pixel2.r * MAX_CHANNEL_VALUE);
    const double g1 = std::floor(pixel1.g * MAX_CHANNEL_VALUE);
    const double g2 = std::floor(pixel2.g * MAX_CHANNEL_VALUE);
    const double b1 = std::floor(pixel1.b * MAX_CHANNEL_VALUE);
    const double b2 = std::floor(pixel2.b * MAX_CHANNEL_VALUE);

    return std::fabs(r1 - r2) + std::fabs(g1 - g2) + std::fabs(b1 - b2);
}

bool AreNumbersEqual(const double val1, const double val2) {
    static const double EPS = 1;  // One, because numbers are whole
    return std::fabs(val1 - val2) <= EPS;
}

image_processor::Image::Channel NormalizeChannelValue(const image_processor::Image::Channel& channel) {
    static const double MAX_CHANNEL_VALUE = 255;

    image_processor::Image::Channel result = channel;
    for (int32_t y = 0; y < channel.size(); ++y) {
        for (int32_t x = 0; x < channel[y].size(); ++x) {
            result[y][x] = floor(result[y][x] * MAX_CHANNEL_VALUE);
        }
    }
    return result;
}

bool AreChannelsEqual(const image_processor::Image::Channel& channel1,
                      const image_processor::Image::Channel& channel2) {
    if (channel1.size() != channel2.size()) {
        return false;
    }
    for (int32_t y = 0; y < channel1.size(); ++y) {
        if (channel1[y].size() != channel2[y].size()) {
            return false;
        }
        for (int32_t x = 0; x < channel1[y].size(); ++x) {
            if (!AreNumbersEqual(channel1[y][x], channel2[y][x])) {
                return false;
            }
        }
    }
    return true;
}
}  // namespace

bool DoesImageDataMatch(image_processor::Image& image, const ImageData& data) {
    const auto [height, width] = image.GetResolution();
    if (height != data.height || width != data.width) {
        return false;
    }
    const std::vector<image_processor::Image::Channel>& channels = image.GetChannels();
    if (channels.size() != 1 && channels.size() != 3) {
        return false;
    }
    if (channels.size() == 1) {
        return AreChannelsEqual(NormalizeChannelValue(channels[0]), data.channels[0]) &&
               AreChannelsEqual(NormalizeChannelValue(channels[0]), data.channels[1]) &&
               AreChannelsEqual(NormalizeChannelValue(channels[0]), data.channels[2]);
    }
    return AreChannelsEqual(NormalizeChannelValue(channels[0]), data.channels[0]) &&
           AreChannelsEqual(NormalizeChannelValue(channels[1]), data.channels[1]) &&
           AreChannelsEqual(NormalizeChannelValue(channels[2]), data.channels[2]);
}

bool AreImagesEqual(const image_processor::Image& image1, const image_processor::Image& image2, const double eps) {
    const auto [height1, width1] = image1.GetResolution();
    const auto [height2, width2] = image2.GetResolution();
    if (height1 != height2 || width1 != width2) {
        return false;
    }
    for (size_t y = 0; y < height1; ++y) {
        for (size_t x = 0; x < width1; ++x) {
            const image_processor::Image::Pixel pixel1 = image1.GetPixel(x, y);
            const image_processor::Image::Pixel pixel2 = image2.GetPixel(x, y);
            if (CalculateDifferenceBetweenPixels(pixel1, pixel2) > eps) {
                return false;
            }
        }
    }
    return true;
}

#endif