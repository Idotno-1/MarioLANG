#include "option.hh"

namespace option_parser
{
    std::optional<Options> parse_options(int argc, char* argv[])
    {
        if (argc < 2)
        {
            std::cerr << "Missing required argument \"path\".\n";
            return {};
        }

        Options options = Options();

        options.path_ = argv[1];

        return options;
    }
} // namespace option_parser