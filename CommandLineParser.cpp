//
// Created by yegor on 19.03.23.
//

#include "CommandLineParser.h"
#include "FiltersInformation.h"

#include <filesystem>

namespace {

const size_t INPUT_FILENAME_POSITION = 1;
const size_t OUTPUT_FILENAME_POSITION = 2;
const size_t FILTERS_ARGUMENTS_START_POSITION = 3;
const size_t MIN_ARGUMENTS_NUMBER = 3;

enum class FILE_ACTION_TYPE { READ, WRITE };

void ValidateFile(const std::filesystem::path& path, const FILE_ACTION_TYPE action) {
    using FilePerms = std::filesystem::perms;

    static const std::filesystem::path VALID_FILE_FORMAT = ".bmp";
    const FilePerms file_permissions = std::filesystem::status(path).permissions();
    if (path.extension() != VALID_FILE_FORMAT) {
        throw std::invalid_argument("The input image has to have bmp format");
    }
    if (action == FILE_ACTION_TYPE::READ) {
        if (!std::filesystem::exists(path)) {
            throw std::invalid_argument("The input image does not exist");
        }
        if (FilePerms::none == (file_permissions & FilePerms::group_read) &&
            FilePerms::none == (file_permissions & FilePerms::others_read) &&
            FilePerms::none == (file_permissions & FilePerms::owner_write)) {
            throw std::invalid_argument("No permisiions to read input file");
        }
    } else {
        if (!std::filesystem::exists(path)) {
            return;
        }
        if (FilePerms::none == (file_permissions & FilePerms::group_read) &&
            FilePerms::none == (file_permissions & FilePerms::others_write) &&
            FilePerms::none == (file_permissions & FilePerms::owner_write)) {
            throw std::invalid_argument("No permisiions to write to output file");
        }
    }
}

bool IsNumber(const std::string& str) {
    if (std::count(str.begin(), str.end(), '-') >= 2) {
        return false;
    }
    size_t points_cnt = 0;
    for (const char& ch : str) {
        if (ch == '-') {
            continue;
        }
        if (ch == '.') {
            if (points_cnt != 0) {
                return false;
            }
            ++points_cnt;
        } else if (!std::isdigit(ch)) {
            return false;
        }
    }
    return true;
}

double ConvertStringToDouble(const std::string_view& str) {
    try {
        double result = std::stod(std::string(str));
        return result;
    } catch (std::invalid_argument) {
        throw std::invalid_argument("Channel parameter should be a number");
    }
}

}  // namespace

namespace image_processor {

void CommandLineParser::Parse(int args_number, char** args_value) {
    if (args_number <= 1) {
        return;
    }
    if (args_number < MIN_ARGUMENTS_NUMBER) {
        throw std::invalid_argument("Invalid arguments: input and output files must be specified");
    }
    input_file_name_ = args_value[INPUT_FILENAME_POSITION];
    output_file_name_ = args_value[OUTPUT_FILENAME_POSITION];
    ValidateFile(input_file_name_, FILE_ACTION_TYPE::READ);
    ValidateFile(output_file_name_, FILE_ACTION_TYPE::WRITE);
    for (size_t i = FILTERS_ARGUMENTS_START_POSITION; i < args_number; ++i) {
        if (args_value[i][0] == '-') {
            filters_description_.push_back(FilterDescriptor(args_value[i]));
        } else {
            if (filters_description_.empty()) {
                throw std::invalid_argument("Invalid filter parameters : unexpected parameter value appeared");
            }
            if (!IsNumber(args_value[i])) {
                throw std::invalid_argument(
                    "Invalid filter parameters : all parameters have to be numbers, got string");
            }
            filters_description_.back().params.push_back(ConvertStringToDouble(args_value[i]));
        }
    }
    for (const FilterDescriptor& descriptor : filters_description_) {
        FiltersInformation::GetValidatorFunction(descriptor.name)(descriptor.params);
    }
}

std::vector<FilterDescriptor> CommandLineParser::GetFiltersDescription() const {
    return filters_description_;
}

std::filesystem::path CommandLineParser::GetInputFileName() const {
    return input_file_name_;
}

std::filesystem::path CommandLineParser::GetOutputFileName() const {
    return output_file_name_;
}

bool CommandLineParser::AreArgumentsEmpty() const {
    return filters_description_.empty() && input_file_name_.empty() && output_file_name_.empty();
}

}  // namespace image_processor