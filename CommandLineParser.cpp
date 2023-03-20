//
// Created by yegor on 19.03.23.
//

#include "CommandLineParser.h"

namespace command_line_parser {

void CommandLineParser::Parse(int argc, char **argv) {
    if (argc < MIN_ARGUMENTS_NUMBER) {
        throw std::invalid_argument("Invalid arguments: input and output files must be specified");
    }
    input_file_name_ = argv[INPUT_FILENAME_POSITION];
    output_file_name_ = argv[OUTPUT_FILENAME_POSITION];
    for (size_t i = FILTERS_ARGUMENTS_START_POSITION; i < argc; ++i) {
        if (argv[i][0] == '-') {
            filters_description_.push_back(FilterDescriptor(argv[i]));
        } else {
            if (filters_description_.empty()) {
                throw std::invalid_argument("Invalid filter parameters : unexpected parameter value appeared");
            }
            filters_description_.back().params.push_back(argv[i]);
        }
    }
}

std::vector<FilterDescriptor> CommandLineParser::GetFiltersDescription() const {
    return filters_description_;
}

std::string_view CommandLineParser::GetInputFileName() const {
    return input_file_name_;
}

std::string_view CommandLineParser::GetOutputFileName() const {
    return output_file_name_;
}
}  // namespace command_line_parser

FilterDescriptor::FilterDescriptor(const std::string_view &name) : name(name) {
}