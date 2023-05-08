#include "BMP.h"
#include "CommandLineParser.h"
#include "Image.h"
#include "FiltersFactory.h"

#include <iostream>
#include <string>

namespace {
void PrintHelpMessage() {
    std::cout << "A simple BMP image processor\n";
    std::cout << "Created by Yegor Trussov, HSE, Faculty of Computer Science\n";
    std::cout << "The processor supports only valid 54-bit bmp images\n";
    std::cout << "The following filters can be applied to images: \n";
    std::cout << " * -crop <width> <height> - Crop the image\n";
    std::cout << " * -gs - Turns the image into a grayscale image\n";
    std::cout << " * -neg - Turns the image into negative (inverts pixels)\n";
    std::cout << " * -sharp - Applies sharpening to the image\n";
    std::cout << " * -edge <threshold> - Shows edges, intensity is defined by threshold\n";
    std::cout << " * -blur <sigma> - Blurs the image with gaussian blur algorithm\n";
    std::cout
        << " * -crystallize <crystals count> - Makes the image look crystallized, details depend on crystals count\n";
}
}  // namespace

int main(int argc, char** argv) {
    image_processor::CommandLineParser parser = image_processor::CommandLineParser();
    try {
        parser.Parse(argc, argv);
    } catch (const std::invalid_argument& e) {
        std::cout << "Error in processor arguments:\n" + std::string(e.what()) + "\n";
        return 0;
    } catch (const std::exception& e) {
        std::cout << "Application crashed with an unexpected error ;(\n";
        return 0;
    }
    if (parser.AreArgumentsEmpty()) {
        PrintHelpMessage();
        return 0;
    }

    try {
        image_processor::Image image = image_processor::BMP::OpenImage(parser.GetInputFileName());

        for (auto& filter : image_processor::FiltersFactory::GetFilters(parser.GetFiltersDescription())) {
            filter->ApplyFilter(image);
        }

        try {
            image_processor::BMP::SaveImage(image, parser.GetOutputFileName());
        } catch (const std::invalid_argument& e) {
            std::cout << "Error while loading the image:\n" + std::string(e.what()) + "\n";
            return 0;
        } catch (const std::bad_alloc&) {
            std::cout << "Not enough memory on the computer to save the image\n";
            return 0;
        }
    } catch (const std::invalid_argument& e) {
        std::cout << "Error while loading the image:\n" + std::string(e.what()) + "\n";
    } catch (const std::bad_alloc&) {
        std::cout << "Not enough memory on the computer to open the image\n";
    } catch (const std::exception&) {
        std::cout << "Application crashed with an unexpected error ;(\n";
    }

    return 0;
}
