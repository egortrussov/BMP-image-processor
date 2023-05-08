//
// Created by yegor on 19.03.23.
//

#include "FiltersFactory.h"
#include "FiltersInformation.h"

namespace image_processor {

std::vector<std::unique_ptr<Filter>> FiltersFactory::GetFilters(
    const std::vector<FilterDescriptor>& filters_description) {
    std::vector<std::unique_ptr<Filter>> result;
    for (const FilterDescriptor& descriptor : filters_description) {
        result.push_back(FiltersInformation::GetMakerFunction(descriptor.name)(descriptor));
    }
    return result;
}
}  // namespace image_processor
