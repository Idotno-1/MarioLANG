#pragma once

#include <vector>

namespace interpretor
{
    class MemoryBand
    {
    public:
        MemoryBand() = default;

        void increase_cursor();
        void decrease_cursor();

        void increase_value();
        void decrease_valie();

    private:
        std::vector<size_t> pos_;
        std::vector<size_t> neg_;

        int cursor_;
    };
} // namespace interpretor