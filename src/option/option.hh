#pragma once

#include <iostream>
#include <optional>
#include <sstream>
#include <string>

namespace option_parser
{
    struct Options
    {
        Options()
        {
            display_ = false;
            delay_ = -1;
        }

        std::string path_; // REQUIRED
        bool display_; // OPTIONAL
        int delay_; // OPTIONAL
    };

    std::optional<Options> parse_options(int argc, char* argv[]);
} // namespace option_parser