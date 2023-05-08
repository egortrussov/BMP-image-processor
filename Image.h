//
// Created by yegor on 07.03.23.
//

#ifndef CPP_HSE_IMAGE_H
#define CPP_HSE_IMAGE_H

#include <vector>
#include <cstdint>

namespace image_processor {

class Image final {
public:
    using Channel = std::vector<std::vector<double>>;

    struct Resolution {
        size_t height;
        size_t width;

        explicit Resolution(const size_t height, const size_t width);
    };

    struct Pixel {
        const double& r;
        const double& g;
        const double& b;
    };

    struct PixelCoordinates {
        size_t x;
        size_t y;

        explicit PixelCoordinates();
        explicit PixelCoordinates(const size_t x, const size_t y);
    };

    explicit Image(const size_t width, const size_t height);

    Resolution GetResolution() const;

    const Pixel GetPixel(const size_t x, const size_t y) const;
    void SetPixelData(const size_t x, const size_t y, const std::vector<double>& color);

    std::vector<Channel>& GetChannels();

private:
    std::vector<Channel> channels_;
};

}  // namespace image_processor

#endif  // CPP_HSE_IMAGE_H
