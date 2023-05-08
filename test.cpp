//
// Created by yegor on 22.03.23.
//

#include <catch.hpp>
#include <cmath>

#include "Image.h"
#include "BMP.h"
#include "CropFilter.h"
#include "SharpeningFilter.h"
#include "GaussianBlurFilter.h"
#include "NegativeFilter.h"
#include "tests_helper.cpp"

namespace {
const std::string INPUT_FILE_PATH = "./test_images/shrek.bmp";
}  // namespace

TEST_CASE("Test combinations of filters") {
    {
        static const std::string OUTPUT_FILE_PATH = "./test_images/shrek_blur_sharp_neg_sharp.bmp";
        image_processor::Image image = image_processor::BMP::OpenImage(INPUT_FILE_PATH);
        image_processor::GaussianBlurFilter blur_filter(3);
        image_processor::SharpeningFilter sharp_filter;
        image_processor::NegativeFilter neg_filter;
        blur_filter.ApplyFilter(image);
        sharp_filter.ApplyFilter(image);
        neg_filter.ApplyFilter(image);
        sharp_filter.ApplyFilter(image);
        image_processor::Image correct_image = image_processor::BMP::OpenImage(OUTPUT_FILE_PATH);
        REQUIRE(AreImagesEqual(image, correct_image, 2));
    }
    {
        static const std::string OUTPUT_FILE_PATH = "./test_images/shrek_neg_neg_blur_sharp_sharp_crop.bmp";
        image_processor::Image image = image_processor::BMP::OpenImage(INPUT_FILE_PATH);
        image_processor::GaussianBlurFilter blur_filter(3);
        image_processor::SharpeningFilter sharp_filter;
        image_processor::NegativeFilter neg_filter;
        image_processor::CropFilter crop_filter(900, 1000);  // NOLINT
        neg_filter.ApplyFilter(image);
        neg_filter.ApplyFilter(image);
        blur_filter.ApplyFilter(image);
        sharp_filter.ApplyFilter(image);
        sharp_filter.ApplyFilter(image);
        crop_filter.ApplyFilter(image);
        image_processor::Image correct_image = image_processor::BMP::OpenImage(OUTPUT_FILE_PATH);
        REQUIRE(AreImagesEqual(image, correct_image, 2));
    }
}
