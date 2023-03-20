//
// Created by yegor on 19.03.23.
//

#include "FiltersFactory.h"

#include <algorithm>

namespace {
bool DoesStringRepresentInteger(const std::string_view& str) {
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

double ConvertStringToNumber(const std::string_view& str) {
    return static_cast<double>(stof(std::string{str.begin(), str.end()}));
}
}  // namespace

namespace filters_factory {

std::unique_ptr<Filter> CreateCropFilter(const FilterDescriptor& description) {
    static const size_t PARAMS_NUMBER = 2;
    if (description.params.size() != PARAMS_NUMBER) {
        throw std::invalid_argument("Invalid number of params in crop filter");
    }
    if (!DoesStringRepresentInteger(description.params[0]) || !DoesStringRepresentInteger(description.params[1])) {
        throw std::invalid_argument("Invalid crop filter argument");
    }
    const size_t width = static_cast<size_t>(ConvertStringToNumber(description.params[0]));
    const size_t height = static_cast<size_t>(ConvertStringToNumber(description.params[1]));
    return std::make_unique<CropFilter>(height, width);
}

std::unique_ptr<Filter> CreateCrystallizeFilter(const FilterDescriptor& description) {
    static const size_t PARAMS_NUMBER = 1;
    if (description.params.size() != PARAMS_NUMBER) {
        throw std::invalid_argument("Invalid number of params in crystallize filter");
    }
    if (!DoesStringRepresentInteger(description.params[0])) {
        throw std::invalid_argument("Invalid crystallize filter argument");
    }
    const ssize_t crystals_count = static_cast<ssize_t>(ConvertStringToNumber(description.params[0]));
    if (crystals_count <= 0) {
        throw std::invalid_argument("Width and height must be positive");
    }
    return std::make_unique<CrystallizeFilter>(crystals_count);
}

std::unique_ptr<Filter> CreateEdgeDetectionFilter(const FilterDescriptor& description) {
    static const size_t PARAMS_NUMBER = 1;
    if (description.params.size() != PARAMS_NUMBER) {
        throw std::invalid_argument("Invalid number of params in edge detection filter");
    }
    const double threshold = ConvertStringToNumber(description.params[0]);
    return std::make_unique<EdgeDetectionFilter>(threshold);
}

std::unique_ptr<Filter> CreateGaussianBlurFilter(const FilterDescriptor& description) {
    static const size_t PARAMS_NUMBER = 1;
    if (description.params.size() != PARAMS_NUMBER) {
        throw std::invalid_argument("Invalid number of params in gaussian blur filter");
    }
    const double sigma = (ConvertStringToNumber(description.params[0]));

    return std::make_unique<GaussianBlurFilter>(sigma);
}

std::unique_ptr<Filter> CreateGrayScaleFilter(const FilterDescriptor& description) {
    static const size_t PARAMS_NUMBER = 0;
    if (description.params.size() != PARAMS_NUMBER) {
        throw std::invalid_argument("Invalid number of params in gray scale filter");
    }
    return std::make_unique<GrayScaleFilter>();
}

std::unique_ptr<Filter> CreateNegativeFilter(const FilterDescriptor& description) {
    static const size_t PARAMS_NUMBER = 0;
    if (description.params.size() != PARAMS_NUMBER) {
        throw std::invalid_argument("Invalid number of params in negative filter");
    }
    return std::make_unique<NegativeFilter>();
}

std::unique_ptr<Filter> CreateSharpeningFilter(const FilterDescriptor& description) {
    static const size_t PARAMS_NUMBER = 0;
    if (description.params.size() != PARAMS_NUMBER) {
        throw std::invalid_argument("Invalid number of params in sharpening filter");
    }
    return std::make_unique<SharpeningFilter>();
}

FiltersFactory::FiltersFactory() {
    filter_makers_["-crop"] = &CreateCropFilter;
    filter_makers_["-crystallize"] = &CreateCrystallizeFilter;
    filter_makers_["-edge"] = &CreateEdgeDetectionFilter;
    filter_makers_["-blur"] = &CreateGaussianBlurFilter;
    filter_makers_["-gs"] = &CreateGrayScaleFilter;
    filter_makers_["-neg"] = &CreateNegativeFilter;
    filter_makers_["-sharp"] = &CreateSharpeningFilter;
}

std::vector<std::unique_ptr<Filter>> FiltersFactory::GetFilters(
    const std::vector<FilterDescriptor>& filters_description) {
    std::vector<std::unique_ptr<Filter>> result;
    for (const FilterDescriptor& descriptor : filters_description) {
        if (filter_makers_.find(descriptor.name) == filter_makers_.end()) {
            throw std::invalid_argument("Unsupported filter value : " + std::string(descriptor.name));
        }
        result.push_back(filter_makers_[descriptor.name](descriptor));
    }
    return result;
}
}  // namespace filters_factory
