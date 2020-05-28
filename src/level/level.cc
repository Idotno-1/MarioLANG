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
        if (!board_.size())
            return false;

        handle_pos();

        while (true)
            if (!do_move() || !apply_gravity() || !handle_pos())
                return false;

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
                    mario_.dir_ = Direction::RIGHT;

                    return true;
                }
        }

        return true;
    }

    bool Level::is_solid(int y, int x)
    {
        if (x < 0 || y < 0 || y >= (int)board_.size()
            || x >= (int)board_[0].size())
            return true;

        return board_[y][x] == '=' || board_[y][x] == '|' || board_[y][x] == '#'
            || board_[y][x] == '\"';
    }

    bool Level::handle_pos()
    {
        char pos = board_[mario_.pos_y_][mario_.pos_x_];

        // handle skip

        if (pos == '+')
            memory_.increase_value();
        else if (pos == '-')
            memory_.decrease_value();
        else if (pos == '(')
            memory_.decrease_cursor();
        else if (pos == ')')
            memory_.increase_cursor();
        else if (pos == '.')
            std::cout << memory_.get_value() % 256;
        else if (pos == ':')
            std::cout << memory_.get_value() << ' ';
        else if (pos == ',')
            std::cout << "TODO";
        else if (pos == ';')
            std::cout << "TODO";
        else if (pos == '<')
        {
            mario_.dir_ = Direction::LEFT;
            if (is_solid(mario_.pos_y_ + 1, mario_.pos_x_))
            {
                display();
                if (!is_solid(mario_.pos_y_, mario_.pos_x_ - 1))
                {
                    mario_.pos_x_--;
                    return handle_pos();
                }
                else
                    return false;
            }
        }
        else if (pos == '>')
        {
            mario_.dir_ = Direction::RIGHT;
            if (is_solid(mario_.pos_y_ + 1, mario_.pos_x_))
            {
                display();
                if (!is_solid(mario_.pos_y_, mario_.pos_x_ + 1))
                {
                    mario_.pos_x_++;
                    return handle_pos();
                }
                else
                    return false;
            }
        }
        else if (pos == '!')
            mario_.dir_ = Direction::IDLE;
        else if (pos == '^')
        {
            mario_.dir_ = Direction::IDLE; // FIXME
            mario_.pos_x_++;
        }
        else if (pos == '@')
            mario_.toggle_dir();
        else if (pos == '[')
        {
            if (mario_.dir_ == Direction::IDLE)
                return false;

            if (!memory_.get_value())
                mario_.skip_ = true;
        }
        else if (is_solid(mario_.pos_y_, mario_.pos_x_))
            return false;

        display();

        return true;
    }

    bool Level::do_move()
    {
        if (is_solid(mario_.pos_y_, mario_.pos_x_ + mario_.dir_))
            return false;

        mario_.pos_x_ += mario_.dir_;

        // Elevator
        if (mario_.dir_ == Direction::IDLE
            && board_[mario_.pos_y_ + 1][mario_.pos_x_] == '#')
        {
            int direction = 0;

            for (size_t i = 1; i < board_.size(); ++i)
                if (board_[i][mario_.pos_x_] == '\"')
                {
                    direction = i > mario_.pos_y_ ? 1 : -1;
                    break;
                }

            return apply_elevator(direction);
        }

        return true;
    }

    bool Level::apply_elevator(int direction)
    {
        if (!direction)
            return false;

        if (direction == 1)
            mario_.pos_y_ -= 2;

        while (board_[mario_.pos_y_ + 1][mario_.pos_x_] != '\"')
        {
            if (!handle_pos() && board_[mario_.pos_y_][mario_.pos_x_] != '\"')
                return false;

            mario_.pos_y_ += direction;
        }

        return true;
    }

    bool Level::apply_gravity()
    {
        while (mario_.pos_y_ < board_.size() - 1
               && !is_solid(mario_.pos_y_ + 1, mario_.pos_x_))
        {
            if (!handle_pos())
                return false;

            mario_.pos_y_++;
        }

        return true;
    }

    void Level::display()
    {
        usleep(100000);

        if (!board_.size())
        {
            std::cout << "# No map loaded #\n";
            return;
        }

        std::cout << std::endl;

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
                         || board_[i][j] == '[' || board_[i][j] == '@'
                         || board_[i][j] == '>' || board_[i][j] == '<')
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

        usleep(500);
    }
} // namespace interpretor