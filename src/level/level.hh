#pragma once

#include <string>

#include "../mario/mario.hh"
#include "../memory-band/memory-band.hh"

namespace interpretor
{
    class Level
    {
    public:
        Level();

        bool load(std::string path);
        bool play();

    private:
        Mario mario_;
    };
}