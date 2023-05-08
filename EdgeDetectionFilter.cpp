//
// Created by yegor on 14.03.23.
//

#include "EdgeDetectionFilter.h"
#include "ConvolutionFilter.h"
#include "ThresholdFilter.h"
#include "GrayScaleFilter.h"

namespace {
const FilterMatrix EDGE_DETECTION_FILTER_MATRIX = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
}

namespace image_processor {

EdgeDetectionFilter::EdgeDetectionFilter(const double threshold) : CompositeFilter({}) {
    AddFilter(std::make_unique<image_processor::GrayScaleFilter>());
    AddFilter(std::make_unique<ConvolutionFilter>(EDGE_DETECTION_FILTER_MATRIX));
    AddFilter(std::make_unique<ThresholdFilter>(threshold));
}

}  // namespace image_processor