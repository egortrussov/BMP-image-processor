//
// Created by yegor on 13.03.23.
//

#include "ConvolutionFilter.h"

#include <iostream>
#include <cmath>

namespace {
using PixelNeighboursMatrix = std::vector<std::vector<double>>;

Image::PixelCoordinates GetClosestValidPixel(const Image::PixelCoordinates& coordinates, const int32_t dx,
                                             const int32_t dy, const Image::Resolution& image_resolution) {
    Image::PixelCoordinates neighbours_coordinates = coordinates;
    if (dx < 0) {
        neighbours_coordinates.x -= std::min(neighbours_coordinates.x, static_cast<size_t>(std::fabs(dx)));
    } else {
        neighbours_coordinates.x = std::min(image_resolution.width - 1, neighbours_coordinates.x + dx);
    }
    if (dy < 0) {
        neighbours_coordinates.y -= std::min(neighbours_coordinates.y, static_cast<size_t>(std::fabs(dy)));
    } else {
        neighbours_coordinates.y = std::min(image_resolution.height - 1, neighbours_coordinates.y + dy);
    }
    return neighbours_coordinates;
}

PixelNeighboursMatrix GetPixelNeighboursMatrix(const Image::Channel& channel,
                                               const Image::PixelCoordinates& coordinates, const int32_t radius,
                                               const Image::Resolution& image_resolution) {
    PixelNeighboursMatrix neighbours(radius * 2 + 1, std::vector<double>(2 * radius + 1));
    for (int32_t dx = -radius; dx <= radius; ++dx) {
        for (int32_t dy = -radius; dy <= radius; ++dy) {
            Image::PixelCoordinates neighbour_coordinates = GetClosestValidPixel(coordinates, dx, dy, image_resolution);
            neighbours[dy + radius][dx + radius] = channel[neighbour_coordinates.y][neighbour_coordinates.x];
            neighbours[dy + radius][dx + radius] = channel[neighbour_coordinates.y][neighbour_coordinates.x];
        }
    }
    return neighbours;
}

double CalculatePixelValue(const PixelNeighboursMatrix& neighbours_matrix, const FilterMatrix& filter_matrix) {
    double value = 0;
    for (size_t i = 0; i < neighbours_matrix.size(); ++i) {
        for (size_t j = 0; j < neighbours_matrix.size(); ++j) {
            value += neighbours_matrix[i][j] * filter_matrix[i][j];
        }
    }
    value = std::max(value, 0.0);
    value = std::min(value, 1.0);
    return value;
}

void ApplyMatrixToChannel(Image::Channel& channel, const FilterMatrix& filter_matrix,
                          const Image::Resolution& image_resolution) {
    const int32_t neighbours_radius = static_cast<int32_t>(filter_matrix.size() / 2);
    Image::Channel new_channel_value(image_resolution.height, std::vector<double>(image_resolution.width, 0));
    for (size_t y = 0; y < channel.size(); ++y) {
        for (size_t x = 0; x < channel[y].size(); ++x) {
            PixelNeighboursMatrix neighbours_matrix =
                GetPixelNeighboursMatrix(channel, Image::PixelCoordinates(x, y), neighbours_radius, image_resolution);
            new_channel_value[y][x] = CalculatePixelValue(neighbours_matrix, filter_matrix);
        }
    }
    channel = new_channel_value;
}

void ApplyMatrixToChannels(Image& image, const FilterMatrix& filter_matrix) {
    std::vector<Image::Channel>& channels = image.GetChannels();
    Image::Resolution image_resolution = image.GetResolution();
    for (Image::Channel& channel : channels) {
        ApplyMatrixToChannel(channel, filter_matrix, image_resolution);
    }
}
}  // namespace

ConvolutionFilter::ConvolutionFilter(FilterMatrix matrix) : matrix_(matrix) {
}

void ConvolutionFilter::ApplyFilter(Image& image) const {
    ApplyMatrixToChannels(image, matrix_);
}