#cmake_minimum_required(VERSION 3.20)
#project(project)
#
#set(CMAKE_CXX_STANDARD 20)
#
#add_executable(
#    image_processor
#    image_processor.cpp BMP.cpp Image.h
#        Image.cpp Filter.h Filter.cpp ChannelWiseFilter.h ChannelWiseFilter.cpp NegativeFilter.h NegativeFilter.cpp GrayScaleFilter.h GrayScaleFilter.cpp CropFilter.h CropFilter.cpp ConvolutionFilter.h ConvolutionFilter.cpp SharpeningFilter.h SharpeningFilter.cpp CompositeFilter.h CompositeFilter.cpp ThresholdFilter.h ThresholdFilter.cpp EdgeDetectionFilter.h EdgeDetectionFilter.cpp GaussianBlurFilter.h GaussianBlurFilter.cpp CrystallizeFilter.h CrystallizeFilter.cpp CommandLineParser.h CommandLineParser.cpp FiltersFactory.h FiltersFactory.cpp)


cmake_minimum_required(VERSION 3.20)

#set(dir ${CMAKE_CURRENT_SOURCE_DIR})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}")

set(CMAKE_CXX_STANDARD 20)
project(project)

#add_executable(
#    image_processor
#    image_processor.cpp BMP.cpp Image.h
#        Image.cpp Filter.h Filter.cpp ChannelWiseFilter.h ChannelWiseFilter.cpp NegativeFilter.h NegativeFilter.cpp GrayScaleFilter.h GrayScaleFilter.cpp CropFilter.h CropFilter.cpp ConvolutionFilter.h ConvolutionFilter.cpp SharpeningFilter.h SharpeningFilter.cpp CompositeFilter.h CompositeFilter.cpp ThresholdFilter.h ThresholdFilter.cpp EdgeDetectionFilter.h EdgeDetectionFilter.cpp GaussianBlurFilter.h GaussianBlurFilter.cpp CrystallizeFilter.h CrystallizeFilter.cpp CommandLineParser.h CommandLineParser.cpp FiltersFactory.h)


#cmake_minimum_required(VERSION 3.20)
#project(project)
#
#set(CMAKE_CXX_STANDARD 20)
#
add_executable(
        image_processor
        image_processor.cpp BMP.cpp Image.h
        Image.cpp Filter.h Filter.cpp ChannelWiseFilter.h ChannelWiseFilter.cpp NegativeFilter.h NegativeFilter.cpp GrayScaleFilter.h GrayScaleFilter.cpp CropFilter.h CropFilter.cpp ConvolutionFilter.h ConvolutionFilter.cpp SharpeningFilter.h SharpeningFilter.cpp CompositeFilter.h CompositeFilter.cpp ThresholdFilter.h ThresholdFilter.cpp EdgeDetectionFilter.h EdgeDetectionFilter.cpp GaussianBlurFilter.h GaussianBlurFilter.cpp CrystallizeFilter.h CrystallizeFilter.cpp CommandLineParser.h CommandLineParser.cpp FiltersFactory.h FiltersFactory.cpp)