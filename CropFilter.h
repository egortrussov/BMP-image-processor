//
// Created by yegor on 11.03.23.
//

#ifndef CPP_HSE_CROPFILTER_H
#define CPP_HSE_CROPFILTER_H

#include "Filter.h"
#include "Image.h"

class CropFilter : public Filter {
public:
    CropFilter(const size_t height, const size_t width);

    void ApplyFilter(Image& image) const override;

    ~CropFilter() override = default;

private:
    size_t height_;
    size_t width_;
};

#endif  // CPP_HSE_CROPFILTER_H
