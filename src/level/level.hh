#pragma once

#include <string>
#include <vector>

#include "../mario/mario.hh"
#include "../memory-band/memory-band.hh"

namespace interpretor
{
    class Level
    {
    public:
        Level() = default;

        bool load(std::string path);
        bool play();

    private:
        Mario mario_;
        MemoryBand memory_;
        std::vector<std::string> board_;

        bool set_start();
        bool do_move(int x, int y);
    };
} // namespace interpretor