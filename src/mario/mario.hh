#pragma once

#include <iostream>

namespace interpretor
{
    enum Direction
    {
        RIGHT = 1,
        LEFT = -1,
        IDLE = 0
    };

    struct Mario
    {
        Mario();

        unsigned pos_x_;
        unsigned pos_y_;

        Direction dir_;

        bool skip_;

        void toggle_dir();
        bool is_stuck();
    };
} // namespace interpretor