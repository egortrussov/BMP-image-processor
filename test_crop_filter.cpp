//
// Created by yegor on 26.03.23.
//

#include <catch.hpp>

#include "tests_helper.cpp"
#include "test_images_data.h"
#include "CropFilter.h"
#include "BMP.h"

TEST_CASE("Test negative filter") {
    {
        static const std::string OUTPUT_FILE_PATH = "./test_images/shrek_crop_200_300.bmp";
        image_processor::Image image = image_processor::BMP::OpenImage("./test_images/shrek.bmp");
        image_processor::CropFilter crop_filter(300, 200);  // NOLINT
        crop_filter.ApplyFilter(image);
        image_processor::Image correct_image = image_processor::BMP::OpenImage(OUTPUT_FILE_PATH);
        REQUIRE(AreImagesEqual(image, correct_image, 0));
    }
    {
        static const std::string OUTPUT_FILE_PATH = "./test_images/shrek_crop_2000_3000.bmp";
        image_processor::Image image = image_processor::BMP::OpenImage("./test_images/shrek.bmp");
        image_processor::CropFilter crop_filter(3000, 2000);  // NOLINT
        crop_filter.ApplyFilter(image);
        image_processor::Image correct_image = image_processor::BMP::OpenImage(OUTPUT_FILE_PATH);
        REQUIRE(AreImagesEqual(image, correct_image, 0));
    }  // too large image resolution
    {
        image_processor::Image image = image_processor::BMP::OpenImage("./test_images/small_image.bmp");
        image_processor::CropFilter crop_filter(3, 4);
        crop_filter.ApplyFilter(image);
        REQUIRE(DoesImageDataMatch(image, IMAGES_DATA.at("small_image_crop_3_4")));
    }  // Test on precalculated dataset
    {
        image_processor::Image image = image_processor::BMP::OpenImage("./test_images/small_image.bmp");
        image_processor::CropFilter crop_filter(300, 400);  // NOLINT
        crop_filter.ApplyFilter(image);
        REQUIRE(DoesImageDataMatch(image, IMAGES_DATA.at("small_image")));
    }  // Test on precalculated dataset
}