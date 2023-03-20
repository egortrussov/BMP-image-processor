//
// Created by yegor on 14.03.23.
//

#ifndef CPP_HSE_EDGEDETECTIONFILTER_H
#define CPP_HSE_EDGEDETECTIONFILTER_H

#include "CompositeFilter.h"
#include "ConvolutionFilter.h"
#include "ThresholdFilter.h"
#include "GrayScaleFilter.h"

class EdgeDetectionFilter : public CompositeFilter {
public:
    explicit EdgeDetectionFilter(const double threshold);

    ~EdgeDetectionFilter() override = default;
};

#endif  // CPP_HSE_EDGEDETECTIONFILTER_H
