//
// Created by yegor on 25.03.23.
//

#include <catch.hpp>

#include "tests_helper.cpp"
#include "test_images_data.h"
#include "GrayScaleFilter.h"
#include "BMP.h"

TEST_CASE("Test grayscale filter") {
    {
        static const std::string OUTPUT_FILE_PATH = "./test_images/shrek_gs.bmp";
        image_processor::Image image = image_processor::BMP::OpenImage("./test_images/shrek.bmp");
        image_processor::GrayScaleFilter gs_filter;
        gs_filter.ApplyFilter(image);
        image_processor::Image correct_image = image_processor::BMP::OpenImage(OUTPUT_FILE_PATH);
        REQUIRE(AreImagesEqual(image, correct_image, 1));
    }
    {
        image_processor::Image image = image_processor::BMP::OpenImage("./test_images/small_image.bmp");
        image_processor::GrayScaleFilter gs_filter;
        gs_filter.ApplyFilter(image);
        REQUIRE(DoesImageDataMatch(image, IMAGES_DATA.at("small_image_gs")));
    }  // Test on precalculated dataset
}