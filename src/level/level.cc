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

        board_.resize(max_y > 0 ? max_y - 1 : 0);

        for (size_t i = 0; i < board_.size(); i++)
            board_[i].resize(max_x, ' ');

        return board_.size() || board_[0].size();
    }

    void Level::play()
    {
        if (!board_.size() || !board_[0].size())
            return;

        display();
        handle_pos();
        apply_gravity();

        while (do_move() && apply_gravity() && handle_pos())
            ;
    }

    bool Level::is_solid(int y, int x)
    {
        if (x < 0 || y < 0 || x >= (int)board_[0].size())
            return true;

        return board_[y][x] == '=' || board_[y][x] == '|' || board_[y][x] == '#'
            || board_[y][x] == '\"';
    }

    bool Level::handle_pos()
    {
        const char pos = board_[mario_.pos_y_][mario_.pos_x_];
        const std::string tokens = "=|#\")(+-.:,;<>^![@";
        int value = 0;

        if (mario_.skip_ && tokens.find(pos) != std::string::npos)
        {
            mario_.skip_ = false;
            return true;
        }

        switch (pos)
        {
        case '+': // Increment current memory cell
            memory_.increase_value();
            break;

        case '-': // Decrement current memory cell
            memory_.decrease_value();
            break;

        case '(': // Move memort pointer left
            memory_.decrease_cursor();
            break;

        case ')': // Move memort pointer right
            memory_.increase_cursor();
            break;

        case '.': // Display ascii value
            std::cout << (char)(memory_.get_value() % 256);
            break;

        case ':': // Display numerical value
            std::cout << memory_.get_value() << ' ';
            break;

        case ',': // Input ascii value
            memory_.set_value(getchar());
            break;

        case ';': // Input numerical value
            scanf("%d", &value);

            memory_.set_value(value);
            break;

        case '<': // Go left
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
            break;

        case '>': // Go right
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
            break;

        case '!': // Stop
            mario_.dir_ = Direction::IDLE;
            break;

        case '^': // Jump

            mario_.dir_ = Direction::IDLE;

            display();
            if (mario_.pos_y_ == 0)
                return false; // Blocked

            mario_.pos_y_--;

            if (board_[mario_.pos_y_][mario_.pos_x_] == '>')
            {
                mario_.dir_ = Direction::RIGHT;
                display();
                if (!is_solid(mario_.pos_y_, mario_.pos_x_ + 1))
                {
                    mario_.pos_x_++;
                    return handle_pos();
                }
                else
                    mario_.pos_y_++;
            }
            else if (board_[mario_.pos_y_][mario_.pos_x_] == '<')
            {
                mario_.dir_ = Direction::LEFT;
                display();
                if (!is_solid(mario_.pos_y_, mario_.pos_x_ - 1))
                {
                    mario_.pos_x_--;
                    return handle_pos();
                }
                else
                    mario_.pos_y_++;
            }
            else
            {
                mario_.dir_ = Direction::IDLE;
                mario_.pos_y_++;
                return false;
            }
            break;

        case '@': // Toggle direction
            mario_.toggle_dir();
            break;

        case '[': // Skip next if 0
            if (!memory_.get_value())
                mario_.skip_ = true;
            break;

        default:
            if (is_solid(mario_.pos_y_, mario_.pos_x_))
                return false;
        }

        display();

        return true;
    }

    bool Level::do_move()
    {
        if (is_solid(mario_.pos_y_, mario_.pos_x_ + mario_.dir_))
            return false;

        mario_.pos_x_ += mario_.dir_;

        // Elevator check
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
            mario_.pos_y_ += 2;

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
        while (mario_.pos_y_ < board_.size()
               && !is_solid(mario_.pos_y_ + 1, mario_.pos_x_))
        {
            if (!handle_pos())
                return false;

            mario_.pos_y_++;
        }

        return mario_.pos_y_ < board_.size();
    }

    void Level::display()
    {
        if (!display_)
            return;

        usleep(delay_ * 1000);

        if (!board_.size())
        {
            std::cout << "# No map loaded #\n";
            return;
        }

        std::cout << std::endl;

        // Upper boundary
        for (size_t i = 0; i < board_[0].size() + 2; ++i)
            std::cout << (i == board_[0].size() + 1 ? " \x1B[0m\n"
                                                    : "\x1B[100m ");

        for (size_t i = 0; i < board_.size(); ++i)
        {
            // Left boundary
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

            // Right boundary
            std::cout << "\x1B[100m \x1B[0m\n";
        }

        // Lower boundary
        for (size_t i = 0; i < board_[0].size() + 2; ++i)
            std::cout << (i == board_[0].size() + 1 ? " \x1B[0m\n"
                                                    : "\x1B[100m ");

        std::cout << std::endl;
        memory_.display();

        usleep(500);
    }
} // namespace interpretor