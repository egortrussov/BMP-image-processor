//
// Created by yegor on 19.03.23.
//

#ifndef CPP_HSE_FILTERSFACTORY_H
#define CPP_HSE_FILTERSFACTORY_H

#include "CommandLineParser.h"
#include "FiltersInformation.h"
#include "Filter.h"

#include <map>
#include <memory>

namespace image_processor {

class FiltersFactory final {
public:
    static std::vector<std::unique_ptr<Filter>> GetFilters(const std::vector<FilterDescriptor>& filters_description);
};

}  // namespace image_processor

#endif  // CPP_HSE_FILTERSFACTORY_H
