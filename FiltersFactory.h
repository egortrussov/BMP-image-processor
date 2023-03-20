//
// Created by yegor on 19.03.23.
//

#ifndef CPP_HSE_FILTERSFACTORY_H
#define CPP_HSE_FILTERSFACTORY_H

#include "CommandLineParser.h"

#include "CropFilter.h"
#include "CrystallizeFilter.h"
#include "EdgeDetectionFilter.h"
#include "GaussianBlurFilter.h"
#include "GrayScaleFilter.h"
#include "NegativeFilter.h"
#include "SharpeningFilter.h"

#include <map>
#include <memory>

namespace filters_factory {

std::unique_ptr<Filter> CreateCropFilter(const FilterDescriptor& description);
std::unique_ptr<Filter> CreateCrystallizeFilter(const FilterDescriptor& description);
std::unique_ptr<Filter> CreateEdgeDetectionFilter(const FilterDescriptor& description);
std::unique_ptr<Filter> CreateGaussianBlurFilter(const FilterDescriptor& description);
std::unique_ptr<Filter> CreateGrayScaleFilter(const FilterDescriptor& description);
std::unique_ptr<Filter> CreateNegativeFilter(const FilterDescriptor& description);
std::unique_ptr<Filter> CreateSharpeningFilter(const FilterDescriptor& description);

class FiltersFactory {
public:
    FiltersFactory();
    std::vector<std::unique_ptr<Filter>> GetFilters(const std::vector<FilterDescriptor>& filters_description);

private:
    using FilterMakerFunction = std::unique_ptr<Filter> (*)(const FilterDescriptor&);

    std::map<std::string_view, FilterMakerFunction> filter_makers_;
};

}  // namespace filters_factory

#endif  // CPP_HSE_FILTERSFACTORY_H
