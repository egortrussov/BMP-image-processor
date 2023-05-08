//
// Created by yegor on 14.03.23.
//

#include "CompositeFilter.h"

namespace image_processor {

CompositeFilter::CompositeFilter(FiltersList filters) : filters_(std::move(filters)) {
}

void CompositeFilter::ApplyFilter(Image& image) const {
    for (const auto& filter : filters_) {
        filter->ApplyFilter(image);
    }
}

void CompositeFilter::AddFilter(std::unique_ptr<Filter> filter_ptr) {
    filters_.push_back(std::move(filter_ptr));
}

}  // namespace image_processor