//
// Created by yegor on 16.03.23.
//

#include "CrystallizeFilter.h"

#include <cmath>
#include <iostream>
#include <random>
#include <limits>

namespace {
std::vector<Image::PixelCoordinates> GenerateRandomCoordinates(const size_t size, const size_t max_x,
                                                               const size_t max_y) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution_x(0, static_cast<int>(max_x));
    std::uniform_int_distribution<> distribution_y(0, static_cast<int>(max_y));
    std::vector<Image::PixelCoordinates> result(size);
    for (auto& coordinate : result) {
        coordinate = Image::PixelCoordinates(distribution_x(gen), distribution_y(gen));
    }
    return result;
}

size_t GetDistanceBetweenPixels(const Image::PixelCoordinates& coordinates_1,
                                const Image::PixelCoordinates& coordinates_2) {
    return (coordinates_1.x - coordinates_2.x) * (coordinates_1.x - coordinates_2.x) +
           (coordinates_1.y - coordinates_2.y) * (coordinates_1.y - coordinates_2.y);
}

void ApplyFilterToChannel(Image::Channel& channel, const std::vector<Image::PixelCoordinates>& crystals_coordinates) {
    Image::Channel new_channel_value = channel;
    for (size_t y = 0; y < channel.size(); ++y) {
        for (size_t x = 0; x < channel[y].size(); ++x) {
            size_t nearest_crystal_index = 0;
            size_t nearest_crystal_distance = std::numeric_limits<size_t>::max();
            for (size_t crystal_index = 0; crystal_index < crystals_coordinates.size(); ++crystal_index) {
                const size_t distance =
                    GetDistanceBetweenPixels(Image::PixelCoordinates(x, y), crystals_coordinates[crystal_index]);
                if (distance < nearest_crystal_distance) {
                    nearest_crystal_distance = distance;
                    nearest_crystal_index = crystal_index;
                }
            }
            const auto [crystal_x, crystal_y] = crystals_coordinates[nearest_crystal_index];
            new_channel_value[y][x] = channel[crystal_y][crystal_x];
        }
    }
    channel = new_channel_value;
}
}  // namespace

CrystallizeFilter::CrystallizeFilter(const size_t crystals_count) : crystals_count_(crystals_count) {
}

void CrystallizeFilter::ApplyFilter(Image& image) const {
    const auto [height, width] = image.GetResolution();
    std::vector<Image::PixelCoordinates> crystals_coordinates =
        GenerateRandomCoordinates(crystals_count_, width - 1, height - 1);
    for (Image::Channel& channel : image.GetChannels()) {
        ApplyFilterToChannel(channel, crystals_coordinates);
    }
}