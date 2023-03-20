//
// Created by yegor on 16.03.23.
//

#ifndef CPP_HSE_CRYSTALLIZEFILTER_H
#define CPP_HSE_CRYSTALLIZEFILTER_H

#include "ChannelWiseFilter.h"
#include "Filter.h"

class CrystallizeFilter : public Filter {
public:
    explicit CrystallizeFilter(const size_t crystals_count);
    void ApplyFilter(Image &image) const override;
    ~CrystallizeFilter() override = default;

private:
    size_t crystals_count_;
};

#endif  // CPP_HSE_CRYSTALLIZEFILTER_H
