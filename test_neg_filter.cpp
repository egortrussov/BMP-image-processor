//
// Created by yegor on 26.03.23.
//

#include <catch.hpp>

#include "tests_helper.cpp"
#include "test_images_data.h"
#include "NegativeFilter.h"
#include "BMP.h"

TEST_CASE("Test negative filter") {
    {
        static const std::string OUTPUT_FILE_PATH = "./test_images/shrek_neg.bmp";
        image_processor::Image image = image_processor::BMP::OpenImage("./test_images/shrek.bmp");
        image_processor::NegativeFilter neg_filter;
        neg_filter.ApplyFilter(image);
        image_processor::Image correct_image = image_processor::BMP::OpenImage(OUTPUT_FILE_PATH);
        REQUIRE(AreImagesEqual(image, correct_image, 0));
    }
    {
        static const std::string OUTPUT_FILE_PATH = "./test_images/shrek_neg_neg.bmp";
        image_processor::Image image = image_processor::BMP::OpenImage("./test_images/shrek.bmp");
        image_processor::NegativeFilter neg_filter;
        neg_filter.ApplyFilter(image);
        neg_filter.ApplyFilter(image);
        image_processor::Image correct_image = image_processor::BMP::OpenImage(OUTPUT_FILE_PATH);
        REQUIRE(AreImagesEqual(image, correct_image, 1));
    }  // Double negative filter
    {
        image_processor::Image image = image_processor::BMP::OpenImage("./test_images/small_image.bmp");
        image_processor::NegativeFilter gs_filter;
        gs_filter.ApplyFilter(image);
        REQUIRE(DoesImageDataMatch(image, IMAGES_DATA.at("small_image_neg")));
    }  // Test on precalculated dataset
}