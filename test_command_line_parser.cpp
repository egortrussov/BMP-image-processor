//
// Created by yegor on 26.03.23.
//

#include <catch.hpp>
#include <cmath>
#include "BMP.h"
#include "CommandLineParser.h"

namespace {
const std::string INPUT_FILE_PATH = "./test_images/shrek.bmp";
const std::string EXECUTABLE_PATH = "./image_processor";

void CheckInvalidArgumentsException(const size_t args_num, const char* args[]) {
    image_processor::CommandLineParser parser;
    REQUIRE_THROWS_AS(parser.Parse(static_cast<int32_t>(args_num), const_cast<char**>(args)),  // NOLINT
                      std::exception);
}
}  // namespace

TEST_CASE("Test cmd parser") {
    {
        const size_t args_num = 3;
        const char* args[args_num] = {EXECUTABLE_PATH.c_str(), "dummy.bmp", ""};
        CheckInvalidArgumentsException(args_num, args);
    }  // invalid input file
    {
        const size_t args_num = 5;
        const char* args[args_num] = {EXECUTABLE_PATH.c_str(), "./test.bmp", "file.bmp", "-cropp", "100"};
        CheckInvalidArgumentsException(args_num, args);
    }  // invalid filter descriptor
    {
        const size_t args_num = 5;
        const char* args[args_num] = {EXECUTABLE_PATH.c_str(), "./test.bmp", "file.bmp", "-crop", "1edede00"};
        CheckInvalidArgumentsException(args_num, args);
    }  // invalid filter params
    {
        const size_t args_num = 6;
        const char* args[args_num] = {EXECUTABLE_PATH.c_str(), "./test.bmp", "file.bmp", "-cropp", "100", "-100-"};
        CheckInvalidArgumentsException(args_num, args);
    }  // invalid filter params
    {
        const size_t args_num = 5;
        const char* args[args_num] = {EXECUTABLE_PATH.c_str(), INPUT_FILE_PATH.c_str(), "./test.bmp", "-crop", "-200"};
        CheckInvalidArgumentsException(args_num, args);
    }  // test invalid arguments in crop filter
    {
        const size_t args_num = 7;
        const char* args[args_num] = {
            EXECUTABLE_PATH.c_str(), INPUT_FILE_PATH.c_str(), "./test.bmp", "-crop", "200", "200", "400"};
        CheckInvalidArgumentsException(args_num, args);
    }  // test invalid arguments number in crop filter
    {
        const size_t args_num = 5;
        const char* args[args_num] = {EXECUTABLE_PATH.c_str(), INPUT_FILE_PATH.c_str(), "./test.bmp", "-edge", "-2"};
        CheckInvalidArgumentsException(args_num, args);
    }  // test invalid arguments in edge detection filter
    {
        const size_t args_num = 6;
        const char* args[args_num] = {
            EXECUTABLE_PATH.c_str(), INPUT_FILE_PATH.c_str(), "./test.bmp", "-edge", "1", "1"};
        CheckInvalidArgumentsException(args_num, args);
    }  // test invalid arguments in edge detection filter
    {
        const size_t args_num = 5;
        const char* args[args_num] = {EXECUTABLE_PATH.c_str(), INPUT_FILE_PATH.c_str(), "./test.bmp", "-blur", "bb"};
        CheckInvalidArgumentsException(args_num, args);
    }  // test invalid arguments in blur filter
    {
        const size_t args_num = 6;
        const char* args[args_num] = {
            EXECUTABLE_PATH.c_str(), INPUT_FILE_PATH.c_str(), "./test.bmp", "-blur", "2", "text"};
        CheckInvalidArgumentsException(args_num, args);
    }  // test invalid arguments in blur filter
    {
        const size_t args_num = 5;
        const char* args[args_num] = {EXECUTABLE_PATH.c_str(), INPUT_FILE_PATH.c_str(), "./test.bmp", "-gs", "2"};
        CheckInvalidArgumentsException(args_num, args);
    }  // test invalid arguments in grayscale filter
    {
        const size_t args_num = 5;
        const char* args[args_num] = {EXECUTABLE_PATH.c_str(), INPUT_FILE_PATH.c_str(), "./test.bmp", "-sharp", "2"};
        CheckInvalidArgumentsException(args_num, args);
    }  // test invalid arguments in sharpening filter
    {
        const size_t args_num = 4;
        const char* args[args_num] = {EXECUTABLE_PATH.c_str(), INPUT_FILE_PATH.c_str(), "./test.bmp", "-crystallize"};
        CheckInvalidArgumentsException(args_num, args);
    }  // test invalid arguments in crystallize filter
}