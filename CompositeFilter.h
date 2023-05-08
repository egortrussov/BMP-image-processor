//
// Created by yegor on 14.03.23.
//

#ifndef CPP_HSE_COMPOSITEFILTER_H
#define CPP_HSE_COMPOSITEFILTER_H

#include "Filter.h"

#include <memory>

namespace image_processor {

class CompositeFilter : public Filter {
public:
    using FiltersList = std::vector<std::unique_ptr<image_processor::Filter>>;

    explicit CompositeFilter(FiltersList filters);

    void ApplyFilter(Image& image) const override;

    ~CompositeFilter() override = default;

protected:
    void AddFilter(std::unique_ptr<Filter> filter_ptr);

private:
    FiltersList filters_;
};

}  // namespace image_processor

#endif  // CPP_HSE_COMPOSITEFILTER_H
