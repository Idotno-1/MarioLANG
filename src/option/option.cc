#include "option.hh"

namespace option_parser
{
    std::optional<Options> parse_options(int argc, char* argv[])
    {
        const std::string display1 = "--animate";
        const std::string display2 = "-a";
        const std::string delay = "-d";

        Options options = Options();

        int i = 1;
        while (i < argc)
        {
            if (!display1.compare(argv[i]) || !display2.compare(argv[i]))
                options.display_ = true;
            else if (!delay.compare(argv[i]))
            {
                if (i == argc - 1)
                {
                    std::cerr << "Missing operand for optional argument "
                                 "\"-d\". Default selected.\n";

                    options.delay_ = -1;
                }
                else
                {
                    ++i;
                    std::stringstream delay_value(argv[i]);
                    delay_value >> options.delay_;
                }
            }
            else if (argv[i][0] != '-')
                options.paths_.push_back(argv[i]);

            ++i;
        }

        if (options.paths_.size() == 0)
        {
            std::cerr << "Missing required argument \"path\".\n";
            return {};
        }

        return options;
    }

} // namespace option_parser
