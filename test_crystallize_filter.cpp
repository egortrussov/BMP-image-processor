//
// Created by yegor on 26.03.23.
//

#include <catch.hpp>

#include "tests_helper.cpp"
#include "test_images_data.h"
#include "CrystallizeFilter.h"
#include "BMP.h"

TEST_CASE("Test crystallize filter") {
    {
        static const std::string OUTPUT_FILE_PATH = "./test_images/shrek_crystallize_1.bmp";
        image_processor::Image image = image_processor::BMP::OpenImage("./test_images/shrek.bmp");
        image_processor::CrystallizeFilter crystallize_filter(1);
        crystallize_filter.ApplyFilter(image);
        image_processor::Image correct_image = image_processor::BMP::OpenImage(OUTPUT_FILE_PATH);
        REQUIRE(AreImagesEqual(image, correct_image, 1));
    }
    {
        static const std::string OUTPUT_FILE_PATH = "./test_images/shrek_crystallize_300.bmp";
        image_processor::Image image = image_processor::BMP::OpenImage("./test_images/shrek.bmp");
        image_processor::CrystallizeFilter crystallize_filter(300);  // NOLINT
        crystallize_filter.ApplyFilter(image);
        image_processor::Image correct_image = image_processor::BMP::OpenImage(OUTPUT_FILE_PATH);
        REQUIRE(AreImagesEqual(image, correct_image, 1));
    }
    {
        image_processor::Image image = image_processor::BMP::OpenImage("./test_images/small_image.bmp");
        image_processor::CrystallizeFilter crystallize_filter(2);
        crystallize_filter.ApplyFilter(image);
        REQUIRE(DoesImageDataMatch(image, IMAGES_DATA.at("small_image_crystallize_2")));
    }  // Test on precalculated dataset
    {
        image_processor::Image image = image_processor::BMP::OpenImage("./test_images/small_image.bmp");
        image_processor::CrystallizeFilter crystallize_filter(1);
        crystallize_filter.ApplyFilter(image);
        REQUIRE(DoesImageDataMatch(image, IMAGES_DATA.at("small_image_crystallize_1")));
    }  // Test on precalculated dataset
    {
        image_processor::Image image = image_processor::BMP::OpenImage("./test_images/small_image.bmp");
        image_processor::CrystallizeFilter crystallize_filter(500);  // NOLINT
        crystallize_filter.ApplyFilter(image);
        REQUIRE(DoesImageDataMatch(image, IMAGES_DATA.at("small_image_crystallize_500")));
    }  // Test on precalculated dataset
}