//
// Created by yegor on 16.03.23.
//

#ifndef CPP_HSE_CRYSTALLIZEFILTER_H
#define CPP_HSE_CRYSTALLIZEFILTER_H

#include "ChannelWiseFilter.h"

namespace image_processor {

namespace {
static const int32_t DEFAULT_SEED_VALUE = 22822869;
}

class CrystallizeFilter final : public ChannelWiseFilter {
public:
    explicit CrystallizeFilter(const size_t crystals_count, const int32_t seed = DEFAULT_SEED_VALUE);

    ~CrystallizeFilter() override = default;

protected:
    void FilterImplementation(Image::Channel& channel) const override;

private:
    size_t crystals_count_;
    int32_t seed_;
};

}  // namespace image_processor

#endif  // CPP_HSE_CRYSTALLIZEFILTER_H
