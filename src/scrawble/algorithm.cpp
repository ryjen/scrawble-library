#include <scrawble/algorithm.h>

namespace scrawble
{
    namespace temp
    {
        struct move {
            lexicon::point start;
            lexicon::point left;
            lexicon::point actual;
            lexicon::direction::type direction;
            std::string word;
            lexicon::node::ptr node;
            std::vector<tile> rack;

            move(const lexicon::point start, const lexicon::point &actual, lexicon::direction::type dir,
                 const std::string &word, const lexicon::node::ptr &node, const std::vector<tile> &rack);

            move copy(char del) const;

            move turn(lexicon::direction::type dir) const;

            lexicon::move convert() const;
        };

        move::move(const lexicon::point start, const lexicon::point &actual, lexicon::direction::type dir,
                   const std::string &word, const lexicon::node::ptr &node, const std::vector<tile> &rack)
            : start(start), left(), actual(actual), direction(dir), word(word), node(node), rack(rack)
        {
        }

        move move::copy(char del) const
        {
            move tmp(*this);
            tmp.rack.erase(std::find(tmp.rack.begin(), tmp.rack.end(), del));
            tmp.node = this->node->find(del);
            switch (tmp.direction) {
                case lexicon::direction::left:
                    tmp.word = std::to_string(del) + this->word;
                    tmp.actual = lexicon::point(actual.x - 1, actual.y);
                    break;
                case lexicon::direction::right:
                    tmp.word = this->word + std::to_string(del);
                    tmp.actual = lexicon::point(actual.x + 1, actual.y);
                    break;
                case lexicon::direction::up:
                    tmp.word = std::to_string(del) + this->word;
                    tmp.actual = lexicon::point(actual.x, actual.y - 1);
                    break;
                case lexicon::direction::down:
                    tmp.word = this->word + std::to_string(del);
                    tmp.actual = lexicon::point(actual.x, actual.y + 1);
                    break;
            }
            return tmp;
        }

        move move::turn(lexicon::direction::type dir) const
        {
            move tmp(*this);
            tmp.direction = dir;
            tmp.start = lexicon::point(actual.x, actual.y);
            tmp.actual = lexicon::point(start.x, start.y);
            tmp.node = node->find('>');
            return tmp;
        }

        lexicon::move move::convert() const
        {
            return lexicon::move(start, word, direction);
        }
    }

    algorithm::algorithm()
    {
        board_.init();
    }

    void algorithm::search(int x, int y, const std::vector<tile> &rack, std::set<lexicon::move> &pool)
    {
        lexicon::node::ptr root;

        if (x < 0 || x >= board::size || y < 0 || y >= board::size) {
            return;
        }

        try {
            if (board_[x][y + 1] != lexicon::node::EMPTY || board_[x][y - 1] != lexicon::node::EMPTY ||
                (board_[x][y] != lexicon::node::EMPTY && board_[x + 1][y] == lexicon::node::EMPTY)) {
                root = dictionary_.reverse();
                recurse_left_right(pool, root, x, y, rack);
            }
        } catch (const std::out_of_range &e) {
        }

        try {
            if (board_[x + 1][y] != lexicon::node::EMPTY || board_[x - 1][y] != lexicon::node::EMPTY ||
                (board_[x][y] != lexicon::node::EMPTY && board_[x][y + 1] == lexicon::node::EMPTY)) {
                root = dictionary_.reverse();
                recurse_up_down(pool, root, x, y, rack);
            }
        } catch (const std::out_of_range &e) {
        }
    }

    void algorithm::recurse_left_right(std::set<lexicon::move> &pool, lexicon::node::ptr root, int x, int y,
                                       const std::vector<tile> &rack)
    {
        if (x < 0 || x >= board::size || y < 0 || y >= board::size) {
            return;
        }

        std::string s;

        int actual = x;

        try {
            while (board_[actual][y] != lexicon::node::EMPTY) {
                root = root->find(board_[actual][y]);
                s = std::to_string(board_[actual][y]) + s;
                actual--;
            }

            temp::move tmp(lexicon::point(x, y), lexicon::point(actual + 1, y), lexicon::direction::left, s, root,
                           rack);

            search_recursive(pool, tmp);
        } catch (const std::out_of_range &e) {
        }
    }

    void algorithm::recurse_up_down(std::set<lexicon::move> &pool, lexicon::node::ptr root, int x, int y,
                                    const std::vector<tile> &rack)
    {
        if (x < 0 || x >= board::size || y < 0 || y >= board::size) {
            return;
        }

        std::string s;

        int actual = y;

        try {
            while (board_[x][actual] != lexicon::node::EMPTY) {
                root = root->find(board_[x][actual]);
                s = std::to_string(board_[actual][y]) + s;
                actual--;
            }

            temp::move tmp(lexicon::point(x, y), lexicon::point(x, actual + 1), lexicon::direction::up, s, root, rack);

            search_recursive(pool, tmp);
        } catch (const std::out_of_range &e) {
        }
    }

    void algorithm::search_recursive(std::set<lexicon::move> &pool, const temp::move &m)
    {
        if (!cross(m, m.node->value())) {
            return;
        }

        if (m.node->marker()) {
            pool.insert(m.convert());
        }

        if (m.node->find(lexicon::node::DIRSYM)) {
            if (m.direction == lexicon::direction::left) {
                search_recursive(pool, m.turn(lexicon::direction::right));
            } else {
                search_recursive(pool, m.turn(lexicon::direction::down));
            }
        }

        if (end_of_board(m)) {
            return;
        }

        auto letter = next_tile(m);

        if (letter != lexicon::node::EMPTY) {
            if (m.node->find(letter)) {
                search_recursive(pool, m.copy(letter));
            }
        } else {
            for (auto tile : m.rack) {
                if (m.node->find(tile.letter())) {
                    search_recursive(pool, m.copy(tile.letter()));
                }
            }
        }
    }

    bool algorithm::end_of_board(const temp::move &m) const
    {
        switch (m.direction) {
            case lexicon::direction::left:
                return m.actual.x - 1 < 0;
            case lexicon::direction::right:
                return m.actual.x + 1 > board::size;
            case lexicon::direction::up:
                return m.actual.y - 1 < 0;
            case lexicon::direction::down:
                return m.actual.y + 1 > board::size;
        }
    }

    char algorithm::next_tile(const temp::move &m) const
    {
        switch (m.direction) {
            case lexicon::direction::left:
                return board_[m.actual.x - 1][m.actual.y];
            case lexicon::direction::right:
                return board_[m.actual.x + 1][m.actual.y];
            case lexicon::direction::up:
                return board_[m.actual.x][m.actual.y - 1];
            case lexicon::direction::down:
                return board_[m.actual.x][m.actual.y + 1];
        }
    }

    bool algorithm::cross(const temp::move &m, char ch) const
    {
        int x = m.actual.x;
        int y = m.actual.y;

        switch (m.direction) {
            case lexicon::direction::left:
            case lexicon::direction::right:
                try {
                    if (board_[x][y + 1] == lexicon::node::EMPTY && board_[x][y - 1] == lexicon::node::EMPTY) {
                        return true;
                    }
                } catch (const std::out_of_range &e) {
                }
                while (--y > 0 && board_[x][y] != lexicon::node::EMPTY) {
                }
                return contains(x, y, true, x, y, ch);
            case lexicon::direction::up:
            case lexicon::direction::down:
                try {
                    if (board_[x + 1][y] == lexicon::node::EMPTY && board_[x - 1][y] == lexicon::node::EMPTY) {
                        return true;
                    }
                } catch (const std::out_of_range &e) {
                }
                while (--x > 0 && board_[x][y] != lexicon::node::EMPTY) {
                }
                return contains(x, y, false, x, y, ch);
        }
    }

    bool algorithm::contains(int x1, int y1, bool down, int x2, int y2, char ch) const
    {
        auto it = dictionary_.begin();

        if (it == dictionary_.end()) {
            return false;
        }

        auto node = *it;

        while (board_[x1][y1] != lexicon::node::EMPTY) {
            auto tmp = node->find(board_[x1][y1]);
            if (!tmp) {
                return false;
            }

            node = tmp;

            if (down)
                y1++;
            else
                x1++;

            if (x1 == x2 && y1 == y2) {
                auto tmp = node->find(ch);
                if (!tmp) {
                    return false;
                }
                node = tmp;

                if (down)
                    y1++;
                else
                    x1++;
            }
            if (x1 >= board::size) return node->marker();
            if (y1 >= board::size) return node->marker();
        }
        return node->marker();
    }
}
