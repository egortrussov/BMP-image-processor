//
// Created by yegor on 13.03.23.
//

#ifndef CPP_HSE_SHARPENINGFILTER_H
#define CPP_HSE_SHARPENINGFILTER_H

#include "ConvolutionFilter.h"

namespace image_processor {

class SharpeningFilter final : public ConvolutionFilter {
public:
    SharpeningFilter();
    ~SharpeningFilter() override = default;
};

}  // namespace image_processor

#endif  // CPP_HSE_SHARPENINGFILTER_H
