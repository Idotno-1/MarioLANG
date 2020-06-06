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

    int error = 0;

    for (auto path : options.value().paths_)
        if (level.load(path))
            level.play();
        else
        {
            std::cerr << F_RED << "ERROR: \"" << path
                      << "\" is not a valid file." << RST << std::endl;

            error = 1;
        }

    return error;
}
