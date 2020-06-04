#include "memory-band.hh"

namespace interpretor
{
    void MemoryBand::increase_cursor()
    {
        ++cursor_;
    }

    void MemoryBand::decrease_cursor()
    {
        --cursor_;
    }

    void MemoryBand::increase_value()
    {
        memory_[cursor_]++;
    }

    void MemoryBand::decrease_value()
    {
        memory_[cursor_]--;
    }

    int MemoryBand::get_value()
    {
        return memory_[cursor_];
    }

    void MemoryBand::set_value(int value)
    {
        memory_[cursor_] = value;
    }

    void MemoryBand::display()
    {
        for (int i = cursor_ - 3; i <= cursor_ + 3; ++i)
            std::cout << (i == cursor_ ? "-> " : "   ") << i
                      << "\t = " << memory_[i] << std::endl;
    }

} // namespace interpretor