//
// Created by yegor on 13.03.23.
//

#include "SharpeningFilter.h"

namespace {
const FilterMatrix SHARPENING_FILTER_MATRIX = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
}

namespace image_processor {

SharpeningFilter::SharpeningFilter() : ConvolutionFilter(SHARPENING_FILTER_MATRIX) {
}

}  // namespace image_processor
