#pragma once

#include <iostream>

namespace interpretor
{
    enum Direction
    {
        RIGHT,
        LEFT,
        IDLE
    };

    struct Mario
    {
        Mario();

        unsigned pos_x_;
        unsigned pos_y_;

        Direction dir_;

        bool flying_;

        void toggle_dir();
    };
} // namespace interpretor