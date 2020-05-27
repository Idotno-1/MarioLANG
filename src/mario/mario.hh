#pragma once

namespace interpretor
{
    enum Direction
    {
        RIGHT,
        LEFT,
        IDLE
    };

    class Mario
    {
    public:
        Mario(int x, int y);

    private:
        int pos_x_;
        int pos_y_;

        Direction dir_;

        bool walking_;
        bool falling_;
    };
} // namespace interpretor