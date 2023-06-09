//
// Created by yegor on 11.03.23.
//

#ifndef CPP_HSE_NEGATIVEFILTER_H
#define CPP_HSE_NEGATIVEFILTER_H

#include "ChannelWiseFilter.h"

namespace image_processor {

class NegativeFilter final : public ChannelWiseFilter {
public:
    ~NegativeFilter() override = default;

protected:
    void FilterImplementation(Image::Channel &channel) const override;
};

}  // namespace image_processor

#endif  // CPP_HSE_NEGATIVEFILTER_H
