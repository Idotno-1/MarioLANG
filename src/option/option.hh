#pragma once

#include <iostream>
#include <optional>
#include <string>

namespace option_parser
{
    struct Options
    {
        std::string path_; // REQUIRED
    };

    std::optional<Options> parse_options(int argc, char* argv[]);
} // namespace option_parser