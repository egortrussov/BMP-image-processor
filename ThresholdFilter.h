//
// Created by yegor on 14.03.23.
//

#ifndef CPP_HSE_THRESHOLDFILTER_H
#define CPP_HSE_THRESHOLDFILTER_H

#include "ChannelWiseFilter.h"

namespace image_processor {

class ThresholdFilter final : public ChannelWiseFilter {
public:
    explicit ThresholdFilter(const double threshold);

    ~ThresholdFilter() override = default;

protected:
    void FilterImplementation(Image::Channel& channel) const override;

private:
    double threshold_;
};

}  // namespace image_processor

#endif  // CPP_HSE_THRESHOLDFILTER_H
