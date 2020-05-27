#include "mario.hh"

namespace interpretor
{
    Mario::Mario(int x, int y)
        : pos_x_(x)
        , pos_y_(y)
    {
        dir_ = Direction::RIGHT;
        walking_ = true;
        falling_ = false;
    }
} // namespace interpretor