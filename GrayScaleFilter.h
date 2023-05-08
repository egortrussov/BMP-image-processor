//
// Created by yegor on 11.03.23.
//

#ifndef CPP_HSE_GRAYSCALEFILTER_H
#define CPP_HSE_GRAYSCALEFILTER_H

#include "Filter.h"

namespace image_processor {

class GrayScaleFilter final : public Filter {
public:
    ~GrayScaleFilter() override = default;

    void ApplyFilter(Image& image) const final;
};

}  // namespace image_processor

#endif  // CPP_HSE_GRAYSCALEFILTER_H
