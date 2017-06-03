#include <scrawble/algorithm.h>
#include <algorithm>
#include <cassert>

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
            scrawble::rack rack;
            int score;

            move(const lexicon::point start, const lexicon::point &actual, lexicon::direction::type dir,
                 const std::string &word, const lexicon::node::ptr &node, const scrawble::rack &rack);

            move copy(const tile &tile) const;

            move turn(lexicon::direction::type dir) const;

            lexicon::move convert() const;
        };

        move::move(const lexicon::point start, const lexicon::point &actual, lexicon::direction::type dir,
                   const std::string &word, const lexicon::node::ptr &node, const scrawble::rack &rack)
            : start(start), left(), actual(actual), direction(dir), word(word), node(node), rack(rack), score(0)
        {
        }

        move move::copy(const tile &tile) const
        {
            auto del = tile.letter();
            move tmp(*this);
            auto it = std::find(tmp.rack.begin(), tmp.rack.end(), del);
            assert(it != tmp.rack.end());
            auto index = std::distance(tmp.rack.begin(), it);
            tmp.rack.pop(index);
            tmp.node = this->node->find(del);
            tmp.score += tile.score();
            assert(tmp.node != nullptr);
            switch (tmp.direction) {
                case lexicon::direction::left:
                    tmp.word = del + this->word;
                    tmp.actual = lexicon::point(actual.x - 1, actual.y);
                    break;
                case lexicon::direction::right:
                    tmp.word = this->word + del;
                    tmp.actual = lexicon::point(actual.x + 1, actual.y);
                    break;
                case lexicon::direction::up:
                    tmp.word = del + this->word;
                    tmp.actual = lexicon::point(actual.x, actual.y - 1);
                    break;
                case lexicon::direction::down:
                    tmp.word = this->word + del;
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
            tmp.node = node->find(lexicon::node::DIRSYM);
            assert(tmp.node != nullptr);
            return tmp;
        }

        lexicon::move move::convert() const
        {
            return lexicon::move(start, word, direction, score);
        }
    }

    algorithm::algorithm()
    {
        board_.init();
    }

    void algorithm::search(int x, int y, const rack &rack, std::set<lexicon::move> &pool)
    {
        lexicon::node::ptr root;

        if (x < 0 || x >= board::size || y < 0 || y >= board::size) {
            return;
        }

        try {
            if (!board_[x][y + 1].empty() || !board_[x][y - 1].empty() ||
                (!board_[x][y].empty() && board_[x + 1][y].empty())) {
                root = dictionary_.reverse();
                if (root != nullptr) {
                    recurse_left_right(pool, root, x, y, rack);
                }
            }
        } catch (const std::out_of_range &e) {
        }

        try {
            if (!board_[x + 1][y].empty() || !board_[x - 1][y].empty() ||
                (!board_[x][y].empty() && board_[x][y + 1].empty())) {
                root = dictionary_.reverse();
                if (root != nullptr) {
                    recurse_up_down(pool, root, x, y, rack);
                }
            }
        } catch (const std::out_of_range &e) {
        }
    }

    void algorithm::recurse_left_right(std::set<lexicon::move> &pool, lexicon::node::ptr root, int x, int y,
                                       const rack &rack)
    {
        if (x < 0 || x >= board::size || y < 0 || y >= board::size) {
            return;
        }

        std::string s;

        int actual = x;

        try {
            while (!board_[actual][y].empty()) {
                auto tmp = root->find(board_[actual][y].letter());
                if (tmp != nullptr) {
                    root = tmp;
                }
                s = board_[actual][y].letter() + s;
                actual--;
            }

            temp::move tmp(lexicon::point(x, y), lexicon::point(actual + 1, y), lexicon::direction::left, s, root,
                           rack);

            search_recursive(pool, tmp);
        } catch (const std::out_of_range &e) {
        }
    }

    void algorithm::recurse_up_down(std::set<lexicon::move> &pool, lexicon::node::ptr root, int x, int y,
                                    const rack &rack)
    {
        if (x < 0 || x >= board::size || y < 0 || y >= board::size) {
            return;
        }

        std::string s;

        int actual = y;

        try {
            while (!board_[x][actual].empty()) {
                auto tmp = root->find(board_[x][actual].letter());
                if (tmp != nullptr) {
                    root = tmp;
                }
                s = board_[actual][y].letter() + s;
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

        auto tile = next_tile(m);

        if (!tile.empty()) {
            if (m.node->find(tile.letter())) {
                search_recursive(pool, m.copy(tile));
            }
        } else {
            for (auto t : m.rack) {
                if (m.node->find(t.letter())) {
                    search_recursive(pool, m.copy(t));
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

    tile algorithm::next_tile(const temp::move &m) const
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
                    if (board_[x][y + 1].empty() && board_[x][y - 1].empty()) {
                        return true;
                    }
                } catch (const std::out_of_range &e) {
                }
                while (--y > 0 && !board_[x][y].empty()) {
                }
                return contains(x, y, true, x, y, ch);
            case lexicon::direction::up:
            case lexicon::direction::down:
                try {
                    if (board_[x + 1][y].empty() && board_[x - 1][y].empty()) {
                        return true;
                    }
                } catch (const std::out_of_range &e) {
                }
                while (--x > 0 && !board_[x][y].empty()) {
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

        while (!board_[x1][y1].empty()) {
            auto tmp = node->find(board_[x1][y1].letter());
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
