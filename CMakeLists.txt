cmake_minimum_required(VERSION 3.20)

#set(dir ${CMAKE_CURRENT_SOURCE_DIR})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}")

set(CMAKE_CXX_STANDARD 20)
project(project)

add_executable(
        image_processor
        image_processor.cpp BMP.cpp Image.h
        Image.cpp Filter.h FiltersInformation.cpp FiltersInformation.h ChannelWiseFilter.h ChannelWiseFilter.cpp NegativeFilter.h NegativeFilter.cpp GrayScaleFilter.h GrayScaleFilter.cpp CropFilter.h CropFilter.cpp ConvolutionFilter.h ConvolutionFilter.cpp SharpeningFilter.h SharpeningFilter.cpp CompositeFilter.h CompositeFilter.cpp ThresholdFilter.h ThresholdFilter.cpp EdgeDetectionFilter.h EdgeDetectionFilter.cpp GaussianBlurFilter.h GaussianBlurFilter.cpp CrystallizeFilter.h CrystallizeFilter.cpp CommandLineParser.h CommandLineParser.cpp FiltersFactory.h FiltersFactory.cpp BMPHeader.h)

add_catch(test_image_processor CrystallizeFilter.cpp FiltersInformation.h FiltersInformation.cpp NegativeFilter.cpp GrayScaleFilter.cpp GaussianBlurFilter.cpp GrayScaleFilter.cpp ThresholdFilter.cpp CompositeFilter.cpp EdgeDetectionFilter.cpp ConvolutionFilter.cpp ChannelWiseFilter.cpp SharpeningFilter.cpp CommandLineParser.cpp CropFilter.cpp Image.cpp BMP.cpp test.cpp)

add_catch(test_bmp_class test_images_data.h BMP.cpp Image.cpp test_bmp_class.cpp)
add_catch(test_grayscale_filter BMP.cpp GrayScaleFilter.cpp Image.cpp test_images_data.h test_grayscale_filter.cpp)
add_catch(test_neg_filter BMP.cpp ChannelWiseFilter.cpp NegativeFilter.cpp Image.cpp test_images_data.h test_neg_filter.cpp)
add_catch(test_blur_filter BMP.cpp ChannelWiseFilter.cpp GaussianBlurFilter.cpp Image.cpp test_images_data.h test_blur_filter.cpp)
add_catch(test_crop_filter BMP.cpp ChannelWiseFilter.cpp CropFilter.cpp Image.cpp test_images_data.h test_crop_filter.cpp)
add_catch(test_edge_detection_filter BMP.cpp ConvolutionFilter.cpp CompositeFilter.cpp GrayScaleFilter.cpp ThresholdFilter.cpp ChannelWiseFilter.cpp EdgeDetectionFilter.cpp Image.cpp test_images_data.h test_edge_detection_filter.cpp)
add_catch(test_sharp_filter BMP.cpp SharpeningFilter.cpp ConvolutionFilter.cpp CompositeFilter.cpp GrayScaleFilter.cpp ThresholdFilter.cpp ChannelWiseFilter.cpp EdgeDetectionFilter.cpp Image.cpp test_images_data.h test_sharp_filter.cpp)
add_catch(test_crystallize_filter BMP.cpp CrystallizeFilter.cpp SharpeningFilter.cpp ConvolutionFilter.cpp CompositeFilter.cpp GrayScaleFilter.cpp ThresholdFilter.cpp ChannelWiseFilter.cpp EdgeDetectionFilter.cpp Image.cpp test_images_data.h test_crystallize_filter.cpp)
add_catch(test_command_line_parser BMP.cpp GaussianBlurFilter.cpp NegativeFilter.cpp CropFilter.cpp CrystallizeFilter.cpp SharpeningFilter.cpp ConvolutionFilter.cpp CompositeFilter.cpp GrayScaleFilter.cpp ThresholdFilter.cpp ChannelWiseFilter.cpp EdgeDetectionFilter.cpp CommandLineParser.cpp Image.cpp test_images_data.h FiltersInformation.cpp test_command_line_parser.cpp)