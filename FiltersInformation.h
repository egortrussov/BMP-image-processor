//
// Created by yegor on 25.03.23.
//

#ifndef CPP_HSE_FILTERSINFORMATION_H
#define CPP_HSE_FILTERSINFORMATION_H

#include "Filter.h"

#include <vector>
#include <memory>
#include <map>
#include <string>

namespace image_processor {
struct FilterDescriptor {
    std::string name;
    std::vector<double> params;

    explicit FilterDescriptor(const std::string_view& name) : name(name) {
    }
};

using FilterMakerFunction = std::unique_ptr<Filter> (*)(const FilterDescriptor&);
using FilterArgumentsValidatorFunction = void (*)(const std::vector<double>&);

class FiltersInformation final {
public:
    struct FilterInformation {
        FilterMakerFunction CreateFilter;
        FilterArgumentsValidatorFunction ValidateArguments;
    };

    static FilterMakerFunction GetMakerFunction(const std::string& filter_name);
    static FilterArgumentsValidatorFunction GetValidatorFunction(const std::string filter_name);
};

}  // namespace image_processor

#endif  // CPP_HSE_FILTERSINFORMATION_H
