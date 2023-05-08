//
// Created by yegor on 11.03.23.
//

#ifndef CPP_HSE_FILTER_H
#define CPP_HSE_FILTER_H

#include "Image.h"

namespace image_processor {

class Filter {
public:
    virtual void ApplyFilter(Image& image) const = 0;

    virtual ~Filter() = default;
};

}  // namespace image_processor

#endif  // CPP_HSE_FILTER_H
