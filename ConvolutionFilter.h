//
// Created by yegor on 13.03.23.
//

#ifndef CPP_HSE_CONVOLUTIONFILTER_H
#define CPP_HSE_CONVOLUTIONFILTER_H

#include <vector>
#include "Filter.h"

namespace {
using FilterMatrix = std::vector<std::vector<double>>;
}

class ConvolutionFilter : public Filter {
public:
    explicit ConvolutionFilter(FilterMatrix matrix);

    void ApplyFilter(Image& image) const override;

    ~ConvolutionFilter() override = default;

private:
    FilterMatrix matrix_;
};

#endif  // CPP_HSE_CONVOLUTIONFILTER_H
