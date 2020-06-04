#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

#include "../mario/mario.hh"
#include "../memory-band/memory-band.hh"

/* COLORS */
#define RST "\x1B[0m"
#define F_RED "\x1B[31m"
#define F_GREEN "\x1B[32m"
#define F_YELLOW "\x1B[33m"
#define F_BLUE "\x1B[34m"
#define F_MAGENTA "\x1B[35m"
#define F_CYAN "\x1B[36m"
#define F_WHITE "\x1B[37m"
#define F_BLACK "\x1B[90m"
#define D_MARIO "\033[7m"

namespace interpretor
{
    class Level
    {
    public:
        Level() = default;

        Level(bool display, int delay)
            : Level()
        {
            display_ = display;
            delay_ = delay < 0 ? 80 : delay;
        }

        bool load(std::string path);
        bool play();
        void display();

    private:
        Mario mario_;
        MemoryBand memory_;
        std::vector<std::string> board_;
        bool display_;
        int delay_;

        bool do_move();
        bool handle_pos();
        bool apply_gravity();
        bool apply_elevator(int direction);

        bool is_solid(int y, int x);
    };
} // namespace interpretor