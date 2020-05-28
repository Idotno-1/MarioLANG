#include "mario.hh"

namespace interpretor
{
    Mario::Mario()
    {
        pos_x_ = 0;
        pos_y_ = 0;

        dir_ = Direction::IDLE;

        flying_ = false;
        skip_ = false;
    }

    void Mario::toggle_dir()
    {
        if (dir_ == Direction::RIGHT)
            dir_ = Direction::LEFT;
        else if (dir_ == Direction::LEFT)
            dir_ = Direction::RIGHT;

        // [DIR] Mario is currently idle. Cannot toggle direction;
    }
} // namespace interpretor