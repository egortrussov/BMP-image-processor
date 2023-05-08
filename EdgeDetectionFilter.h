//
// Created by yegor on 14.03.23.
//

#ifndef CPP_HSE_EDGEDETECTIONFILTER_H
#define CPP_HSE_EDGEDETECTIONFILTER_H

#include "CompositeFilter.h"

namespace image_processor {

class EdgeDetectionFilter final : public CompositeFilter {
public:
    explicit EdgeDetectionFilter(const double threshold);

    ~EdgeDetectionFilter() override = default;
};

}  // namespace image_processor

#endif  // CPP_HSE_EDGEDETECTIONFILTER_H
