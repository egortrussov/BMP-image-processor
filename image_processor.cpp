#include "BMP.h"
#include "CommandLineParser.h"
#include "Image.h"
#include "FiltersFactory.h"

int main(int argc, char** argv) {
    command_line_parser::CommandLineParser parser = command_line_parser::CommandLineParser();
    parser.Parse(argc, argv);
    Image image = BMP::OpenImage(parser.GetInputFileName());

    filters_factory::FiltersFactory filters_factory = filters_factory::FiltersFactory();
    for (auto& filter : filters_factory.GetFilters(parser.GetFiltersDescription())) {
        std::cout << "Applying filter\n";
        filter->ApplyFilter(image);
    }

    BMP::SaveImage(image, parser.GetOutputFileName());

    return 0;
}
