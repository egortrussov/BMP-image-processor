//
// Created by yegor on 15.03.23.
//

#ifndef CPP_HSE_GAUSSIANBLURFILTER_H
#define CPP_HSE_GAUSSIANBLURFILTER_H

#include "ChannelWiseFilter.h"

class GaussianBlurFilter : public ChannelWiseFilter {
public:
    explicit GaussianBlurFilter(const double sigma);

    ~GaussianBlurFilter() override = default;

protected:
    void FilterImplementation(Image::Channel& channel) const override;

private:
    enum class BlurApplicationType { HORISONTAL, VERTICAL };

    void ApplyBlurToChannel(Image::Channel& channel, BlurApplicationType type) const;

    double sigma_;
};

#endif  // CPP_HSE_GAUSSIANBLURFILTER_H
