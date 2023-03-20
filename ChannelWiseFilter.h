//
// Created by yegor on 11.03.23.
//

#ifndef CPP_HSE_CHANNELWISEFILTER_H
#define CPP_HSE_CHANNELWISEFILTER_H

#include "Filter.h"

class ChannelWiseFilter : public Filter {
public:
    ~ChannelWiseFilter() override = default;

    void ApplyFilter(Image& image) const final;

protected:
    virtual void FilterImplementation(Image::Channel& channel) const = 0;
};

#endif  // CPP_HSE_CHANNELWISEFILTER_H
