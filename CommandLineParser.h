//
// Created by yegor on 19.03.23.
//

#ifndef CPP_HSE_COMMANDLINEPARSER_H
#define CPP_HSE_COMMANDLINEPARSER_H

#include <iostream>
#include <vector>

struct FilterDescriptor {
    std::string_view name;
    std::vector<std::string_view> params;

    explicit FilterDescriptor(const std::string_view& name);
};

namespace command_line_parser {
class CommandLineParser {
public:
    void Parse(int argc, char** argv);
    std::vector<FilterDescriptor> GetFiltersDescription() const;
    std::string_view GetInputFileName() const;
    std::string_view GetOutputFileName() const;

private:
    static const size_t INPUT_FILENAME_POSITION = 1;
    static const size_t OUTPUT_FILENAME_POSITION = 2;
    static const size_t FILTERS_ARGUMENTS_START_POSITION = 3;
    static const size_t MIN_ARGUMENTS_NUMBER = 3;

    std::string_view input_file_name_;
    std::string_view output_file_name_;
    std::vector<FilterDescriptor> filters_description_;
};

}  // namespace command_line_parser

#endif  // CPP_HSE_COMMANDLINEPARSER_H
