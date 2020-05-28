#include "level.hh"

namespace interpretor
{
    bool Level::load(std::string path)
    {
        std::ifstream cf(path);

        board_.resize(15);
        size_t max_y = 0;
        size_t max_x = 0;

        for (max_y = 0; cf.good(); max_y++)
        {
            if (max_y + 1 > board_.size())
                board_.resize(board_.size() * 2);

            std::getline(cf, board_[max_y]);

            if (board_[max_y].size() > max_x)
                max_x = board_[max_y].size();
        }

        cf.close();

        board_.resize(max_y - 1);

        for (size_t i = 0; i < board_.size(); i++)
            board_[i].resize(max_x, ' ');

        return set_start();
    }

    bool Level::play()
    {
        return true;
    }

    bool Level::set_start()
    {
        if (!board_.size())
            return true;

        for (size_t x = 0; x < board_[0].size(); x++)
        {
            for (size_t y = 0; y < board_.size(); y++)
                if (board_[y][x] == '=' || board_[y][x] == '\"'
                    || board_[y][x] == '|' || board_[y][x] == '#')
                {
                    if (y == 0)
                        return false;

                    mario_.pos_x_ = x;
                    mario_.pos_y_ = y - 1;

                    return true;
                }
        }

        return true;
    }

    bool Level::do_move(int x, int y)
    {
        return x != y;
    }

    void Level::display()
    {
        if (!board_.size())
        {
            std::cout << "# No map loaded #\n";
            return;
        }

        for (size_t i = 0; i < board_[0].size() + 2; ++i)
            std::cout << (i == board_[0].size() + 1 ? " \x1B[0m\n"
                                                    : "\x1B[100m ");

        for (size_t i = 0; i < board_.size(); ++i)
        {
            std::cout << "\x1B[100m \x1B[0m";

            for (size_t j = 0; j < board_[i].size(); ++j)
            {
                if (mario_.pos_x_ == j && mario_.pos_y_ == i)
                    std::cout << D_MARIO;

                if (board_[i][j] == '(' || board_[i][j] == ')')
                    std::cout << F_BLUE;
                else if (board_[i][j] == '+')
                    std::cout << F_GREEN;
                else if (board_[i][j] == '-')
                    std::cout << F_RED;
                else if (board_[i][j] == '#' || board_[i][j] == '\"')
                    std::cout << F_MAGENTA;
                else if (board_[i][j] == '.' || board_[i][j] == ':'
                         || board_[i][j] == ',' || board_[i][j] == ';')
                    std::cout << F_CYAN;
                else if (board_[i][j] == '^' || board_[i][j] == '!'
                         || board_[i][j] == '[' || board_[i][j] == '@')
                    std::cout << F_YELLOW;

                std::cout << board_[i][j] << RST;
            }

            std::cout << "\x1B[100m \x1B[0m\n";
        }

        for (size_t i = 0; i < board_[0].size() + 2; ++i)
            std::cout << (i == board_[0].size() + 1 ? " \x1B[0m\n"
                                                    : "\x1B[100m ");

        std::cout << std::endl;
        memory_.display();
    }
} // namespace interpretor