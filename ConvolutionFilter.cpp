//
// Created by yegor on 13.03.23.
//

#include "ConvolutionFilter.h"

#include <cmath>

namespace image_processor {

namespace {

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

void ApplyMatrixToChannel(Image::Channel& channel, const FilterMatrix& filter_matrix,
                          const Image::Resolution& image_resolution) {
    const int32_t neighbours_radius = static_cast<int32_t>(filter_matrix.size() / 2);
    Image::Channel new_channel_value(image_resolution.height, std::vector<double>(image_resolution.width, 0));
    for (size_t y = 0; y < channel.size(); ++y) {
        for (size_t x = 0; x < channel[y].size(); ++x) {

            for (int32_t dx = -neighbours_radius; dx <= neighbours_radius; ++dx) {
                for (int32_t dy = -neighbours_radius; dy <= neighbours_radius; ++dy) {
                    Image::PixelCoordinates neighbour_coordinates =
                        GetClosestValidPixel(Image::PixelCoordinates(x, y), dx, dy, image_resolution);
                    new_channel_value[y][x] += channel[neighbour_coordinates.y][neighbour_coordinates.x] *
                                               filter_matrix[dy + neighbours_radius][dx + neighbours_radius];
                }
            }
            new_channel_value[y][x] = std::min(new_channel_value[y][x], 1.0);
            new_channel_value[y][x] = std::max(new_channel_value[y][x], 0.0);
        }
    }
    channel = new_channel_value;
}
}  // namespace

ConvolutionFilter::ConvolutionFilter(const FilterMatrix& matrix) : matrix_(matrix) {
}

void ConvolutionFilter::FilterImplementation(Image::Channel& channel) const {
    if (channel.empty()) {
        return;
    }
    Image::Resolution resolution(channel.size(), channel[0].size());
    ApplyMatrixToChannel(channel, matrix_, resolution);
}

}  // namespace image_processor