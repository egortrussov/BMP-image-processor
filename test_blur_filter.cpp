//
// Created by yegor on 26.03.23.
//

#include <catch.hpp>

#include "tests_helper.cpp"
#include "test_images_data.h"
#include "GaussianBlurFilter.h"
#include "BMP.h"

TEST_CASE("Test Blur filter") {
    {
        static const std::string OUTPUT_FILE_PATH = "./test_images/shrek_blur.bmp";
        image_processor::Image image = image_processor::BMP::OpenImage("./test_images/shrek.bmp");
        image_processor::GaussianBlurFilter blur_filter(5);  // NOLINT
        blur_filter.ApplyFilter(image);
        image_processor::Image correct_image = image_processor::BMP::OpenImage(OUTPUT_FILE_PATH);
        REQUIRE(AreImagesEqual(image, correct_image, 1));
    }
    {
        static const std::string OUTPUT_FILE_PATH = "./test_images/shrek_blur_blur.bmp";
        image_processor::Image image = image_processor::BMP::OpenImage("./test_images/shrek.bmp");
        image_processor::GaussianBlurFilter blur_filter(5);   // NOLINT
        image_processor::GaussianBlurFilter blur_filter1(1);  // NOLINT
        blur_filter.ApplyFilter(image);
        blur_filter1.ApplyFilter(image);
        image_processor::Image correct_image = image_processor::BMP::OpenImage(OUTPUT_FILE_PATH);
        REQUIRE(AreImagesEqual(image, correct_image, 1));
    }
    {
        image_processor::Image image = image_processor::BMP::OpenImage("./test_images/small_image.bmp");
        image_processor::GaussianBlurFilter blur_filter(2);
        blur_filter.ApplyFilter(image);
        REQUIRE(DoesImageDataMatch(image, IMAGES_DATA.at("small_image_blur")));
    }  // Test on precalculated dataset
}