//
// Created by yegor on 25.03.23.
//

#include "FiltersInformation.h"
#include "CropFilter.h"
#include "CrystallizeFilter.h"
#include "EdgeDetectionFilter.h"
#include "GaussianBlurFilter.h"
#include "GrayScaleFilter.h"
#include "NegativeFilter.h"
#include "SharpeningFilter.h"

#include <cmath>

namespace image_processor {

namespace {

bool IsInteger(const double value) {
    static const double EPS = 1e-5;
    return (value - std::floor(value)) < EPS;
}

}  // namespace

void ValidateCropFilterParams(const std::vector<double>& params) {
    if (params.size() != 2) {
        throw std::invalid_argument("Invalid number of params in crop filter : expected 2");
    }
    for (const double param : params) {
        if (!IsInteger(param) || param < 0) {
            throw std::invalid_argument("Crop params have to be positive integers");
        }
    }
}
std::unique_ptr<Filter> CreateCropFilter(const FilterDescriptor& description) {
    ValidateCropFilterParams(description.params);
    const size_t width = static_cast<size_t>(description.params[0]);
    const size_t height = static_cast<size_t>(description.params[1]);
    return std::make_unique<CropFilter>(height, width);
}

void ValidateCrystallizeFilterParams(const std::vector<double>& params) {
    if (params.size() != 1) {
        throw std::invalid_argument("Invalid number of params in crystallize filter : expected 1");
    }
    for (const double param : params) {
        if (!IsInteger(param) || param < 0) {
            throw std::invalid_argument("Crystallize params have to be positive integers");
        }
    }
}
std::unique_ptr<Filter> CreateCrystallizeFilter(const FilterDescriptor& description) {
    ValidateCrystallizeFilterParams(description.params);
    const size_t crystals_count = static_cast<size_t>(description.params[0]);
    return std::make_unique<CrystallizeFilter>(crystals_count);
}

void ValidateEdgeDetectionFilterParams(const std::vector<double>& params) {
    if (params.size() != 1) {
        throw std::invalid_argument("Invalid number of params in edge detection filter : expected 1");
    }
}
std::unique_ptr<Filter> CreateEdgeDetectionFilter(const FilterDescriptor& description) {
    ValidateEdgeDetectionFilterParams(description.params);
    const double threshold = description.params[0];
    return std::make_unique<EdgeDetectionFilter>(threshold);
}

void ValidateBlurFilterParams(const std::vector<double>& params) {
    if (params.size() != 1) {
        throw std::invalid_argument("Invalid number of params in edge detection filter : expected 1");
    }
    for (const double param : params) {
        if (param < 0) {
            throw std::invalid_argument("Blur params has to be a positive float");
        }
    }
}
std::unique_ptr<Filter> CreateGaussianBlurFilter(const FilterDescriptor& description) {
    ValidateBlurFilterParams(description.params);
    const double sigma = description.params[0];
    return std::make_unique<GaussianBlurFilter>(sigma);
}

void ValidateGrayscaleFilterParams(const std::vector<double>& params) {
    if (!params.empty()) {
        throw std::invalid_argument("Invalid number of params in grayscale filter : expected 0");
    }
}
std::unique_ptr<Filter> CreateGrayScaleFilter(const FilterDescriptor& description) {
    ValidateGrayscaleFilterParams(description.params);
    return std::make_unique<GrayScaleFilter>();
}

void ValidateNegativeFilterParams(const std::vector<double>& params) {
    if (!params.empty()) {
        throw std::invalid_argument("Invalid number of params in negative filter : expected 1");
    }
}
std::unique_ptr<Filter> CreateNegativeFilter(const FilterDescriptor& description) {
    return std::make_unique<NegativeFilter>();
}

void ValidateSharpeningFilterParams(const std::vector<double>& params) {
    if (!params.empty()) {
        throw std::invalid_argument("Invalid number of params in sharpening filter : expected 0");
    }
}
std::unique_ptr<Filter> CreateSharpeningFilter(const FilterDescriptor& description) {
    return std::make_unique<SharpeningFilter>();
}

static const std::map<std::string, FiltersInformation::FilterInformation> FILTERS_INFORMATION{
    {"-crop", {CreateCropFilter, ValidateCropFilterParams}},
    {"-crystallize", {CreateCrystallizeFilter, ValidateCrystallizeFilterParams}},
    {"-edge", {CreateEdgeDetectionFilter, ValidateEdgeDetectionFilterParams}},
    {"-blur", {CreateGaussianBlurFilter, ValidateBlurFilterParams}},
    {"-gs", {CreateGrayScaleFilter, ValidateGrayscaleFilterParams}},
    {"-neg", {CreateNegativeFilter, ValidateNegativeFilterParams}},
    {"-sharp", {CreateSharpeningFilter, ValidateSharpeningFilterParams}},
};

FilterMakerFunction FiltersInformation::GetMakerFunction(const std::string& filter_name) {
    if (FILTERS_INFORMATION.find(filter_name) == FILTERS_INFORMATION.end()) {
        throw std::invalid_argument("Unknown filter name: " + filter_name);
    }
    return FILTERS_INFORMATION.at(filter_name).CreateFilter;
}

FilterArgumentsValidatorFunction FiltersInformation::GetValidatorFunction(const std::string filter_name) {
    if (FILTERS_INFORMATION.find(filter_name) == FILTERS_INFORMATION.end()) {
        throw std::invalid_argument("Unknown filter name: " + filter_name);
    }
    return FILTERS_INFORMATION.at(filter_name).ValidateArguments;
}

}  // namespace image_processor