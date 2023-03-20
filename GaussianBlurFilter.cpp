//
// Created by yegor on 15.03.23.
//

#include "GaussianBlurFilter.h"

#include <cmath>
#include <iostream>

namespace {
double CalculateGaussianFunction(const int32_t dx, const int32_t dy, const double sigma) {
    return std::pow(M_E, (-static_cast<double>(dx) * static_cast<double>(dx) -
                          static_cast<double>(dy) * static_cast<double>(dy)) /
                             (2 * sigma * sigma)) /
           (2 * M_PI * sigma * sigma);
}

bool AreValidNeighbourCoordinates(const size_t x, const int32_t dist, const size_t limit) {
    if (dist < 0) {
        return static_cast<size_t>(std::fabs(dist)) <= x;
    }
    return x + dist < limit;
}
}  // namespace

GaussianBlurFilter::GaussianBlurFilter(const double sigma) : sigma_(sigma) {
}

void GaussianBlurFilter::FilterImplementation(Image::Channel& channel) const {
    ApplyBlurToChannel(channel, BlurApplicationType::HORISONTAL);
    ApplyBlurToChannel(channel, BlurApplicationType::VERTICAL);
}

void GaussianBlurFilter::ApplyBlurToChannel(Image::Channel& channel, BlurApplicationType type) const {
    Image::Channel new_channel_value(channel.size(), std::vector<double>(channel[0].size(), 0));
    const int32_t radius = static_cast<int32_t>(sigma_ * 3);
    for (size_t y = 0; y < channel.size(); ++y) {
        for (size_t x = 0; x < channel[y].size(); ++x) {
            double coefficients_sum = 0;
            for (int32_t d = -radius; d <= radius; ++d) {
                if (type == BlurApplicationType::HORISONTAL) {
                    if (AreValidNeighbourCoordinates(x, d, channel[y].size())) {
                        double coeff = CalculateGaussianFunction(d, 0, sigma_);
                        coefficients_sum += coeff;
                        new_channel_value[y][x] += channel[y][x + d] * coeff;
                    }
                } else {
                    if (AreValidNeighbourCoordinates(y, d, channel.size())) {
                        double coeff = CalculateGaussianFunction(0, d, sigma_);
                        coefficients_sum += coeff;
                        new_channel_value[y][x] += channel[y + d][x] * coeff;
                    }
                }
            }
            new_channel_value[y][x] /= coefficients_sum;
        }
    }
    channel = new_channel_value;
}