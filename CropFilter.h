//
// Created by yegor on 11.03.23.
//

#ifndef CPP_HSE_CROPFILTER_H
#define CPP_HSE_CROPFILTER_H

#include "ChannelWiseFilter.h"
#include "Image.h"

namespace image_processor {

class CropFilter final : public ChannelWiseFilter {
public:
    CropFilter(const size_t height, const size_t width);

    ~CropFilter() override = default;

protected:
    void FilterImplementation(Image::Channel& channel) const override;

private:
    size_t height_;
    size_t width_;
};

}  // namespace image_processor

#endif  // CPP_HSE_CROPFILTER_H
