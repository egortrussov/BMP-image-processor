//
// Created by yegor on 13.03.23.
//

#ifndef CPP_HSE_CONVOLUTIONFILTER_H
#define CPP_HSE_CONVOLUTIONFILTER_H

#include "ChannelWiseFilter.h"

#include <vector>

namespace {
using FilterMatrix = std::vector<std::vector<double>>;
}

namespace image_processor {

class ConvolutionFilter : public ChannelWiseFilter {
public:
    explicit ConvolutionFilter(const FilterMatrix& matrix);

    ~ConvolutionFilter() override = default;

protected:
    void FilterImplementation(Image::Channel& channel) const override;

private:
    FilterMatrix matrix_;
};

}  // namespace image_processor

#endif  // CPP_HSE_CONVOLUTIONFILTER_H
