#include <iostream>
#include <optional>

#include "level/level.hh"
#include "option/option.hh"

int main(int argc, char* argv[])
{
    auto options = option_parser::parse_options(argc, argv);

    if (!options.has_value())
        return 1;

    interpretor::Level level =
        interpretor::Level(options.value().display_, options.value().delay_);

    if (level.load(options.value().path_))
        level.play();
    else
        std::cerr << "Please select a valid file.";

    return 0;
}
