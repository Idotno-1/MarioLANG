#pragma once

#include <map>

namespace interpretor
{
    class MemoryBand
    {
    public:
        MemoryBand() = default;

        void increase_cursor();
        void decrease_cursor();

        void increase_value();
        void decrease_value();

        size_t get_value();

    private:
        std::map<int, size_t> memory_;
        int cursor_;
    };
} // namespace interpretor