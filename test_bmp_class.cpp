//
// Created by yegor on 25.03.23.
//

#include <catch.hpp>

#include "BMP.h"
#include "test_images_data.h"
#include "tests_helper.cpp"

#include <cmath>

TEST_CASE("Open valid images") {
    {
        static const std::string FILE_PATH = "./test_images/shrek.bmp";
        REQUIRE_NOTHROW(image_processor::BMP::OpenImage(FILE_PATH));
    }
}

TEST_CASE("Open invalid files") {
    {
        static const std::string FILE_PATH = "./test_images/programmer.jpg";
        REQUIRE_THROWS_AS(image_processor::BMP::OpenImage(FILE_PATH), std::invalid_argument);
    }
    {
        static const std::string FILE_PATH = "./test_images/random_file.txt";
        REQUIRE_THROWS_AS(image_processor::BMP::OpenImage(FILE_PATH), std::invalid_argument);
    }
    {
        static const std::string FILE_PATH = "./test_images/monke.bmp";
        REQUIRE_THROWS_AS(image_processor::BMP::OpenImage(FILE_PATH), std::invalid_argument);
    }  // Incorrect header
    {
        static const std::string FILE_PATH = "./test_images/non_existing_file.bmp";
        REQUIRE_THROWS_AS(image_processor::BMP::OpenImage(FILE_PATH), std::invalid_argument);
    }  // Incorrect header
}

TEST_CASE("Test correct image object") {
    {
        static const std::string FILE_PATH = "./test_images/small_image.bmp";
        image_processor::Image image = image_processor::BMP::OpenImage(FILE_PATH);
        REQUIRE(DoesImageDataMatch(image, IMAGES_DATA.at("small_image")));
    }
    {
        static const std::string FILE_PATH = "./test_images/shrek.bmp";
        image_processor::Image image = image_processor::BMP::OpenImage(FILE_PATH);
        const auto [height, width] = image.GetResolution();
        for (const image_processor::Image::Channel& channel : image.GetChannels()) {
            if (channel.size() != height) {
                FAIL("Channel height is wrong");
            }
            for (const auto& row : channel) {
                if (row.size() != width) {
                    FAIL("Channel width is wrong");
                }
            }
        }
    }  // check if number of els in channels is correct
    {
        static const std::string FILE_PATH = "./test_images/small_image.bmp";
        image_processor::Image image = image_processor::BMP::OpenImage(FILE_PATH);
        for (const image_processor::Image::Channel& channel : image.GetChannels()) {
            for (int32_t y = 0; y < channel.size(); ++y) {
                for (int32_t x = 0; x < channel.size(); ++x) {
                    if (channel[y][x] < 0 || channel[y][x] > 1) {
                        FAIL("A channel value is less than 0 or greater than 1");
                    }
                }
            }
        }
    }  // Check if all values in channel are positive and less than 1
}
