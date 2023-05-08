//
// Created by yegor on 19.03.23.
//

#ifndef CPP_HSE_COMMANDLINEPARSER_H
#define CPP_HSE_COMMANDLINEPARSER_H

#include "FiltersInformation.h"

#include <vector>
#include <filesystem>

namespace image_processor {

class CommandLineParser {
public:
    void Parse(int args_number, char** args_value);
    std::vector<FilterDescriptor> GetFiltersDescription() const;
    std::filesystem::path GetInputFileName() const;
    std::filesystem::path GetOutputFileName() const;
    bool AreArgumentsEmpty() const;

private:
    std::filesystem::path input_file_name_;
    std::filesystem::path output_file_name_;
    std::vector<FilterDescriptor> filters_description_;
};

}  // namespace image_processor

#endif  // CPP_HSE_COMMANDLINEPARSER_H
