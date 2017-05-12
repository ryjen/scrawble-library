#include <scrawble/lexicon/node.h>
#include <scrawble/scrawble.h>
#include <cassert>
#include <fstream>

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
            lexicon::node node;
            std::vector<char> rack;

            move(const lexicon::point start, const lexicon::point &actual, lexicon::direction::type dir,
                 const std::string &word, const lexicon::node &node, const std::vector<tile> &rack)
                : start(start), left(), actual(actual), direction(dir), word(word), node(node), rack(rack)
            {
            }

            move copy(char del) const
            {
                move tmp(*this);
                tmp.rack.erase(del);
                tmp.node = this->node.find(del);
                switch (tmp.direction) {
                    case direction::left:
                        tmp.word = std::to_string(del) + this->word;
                        tmp.actual = lexicon::point(actual.x - 1, actual.y);
                        break;
                    case direction::right:
                        tmp.word = this->word + std::to_string(del);
                        tmp.actual = lexicon::point(actual.x + 1, actual.y);
                        break;
                    case direction::up:
                        tmp.word = std::to_string(del) + this->word;
                        tmp.actual = lexicon::point(actual.x, actual.y - 1);
                        break;
                    case direction::down:
                        tmp.word = this->word + std::to_string(del);
                        tmp.actual = lexicon::point(actual.x, actual.y + 1);
                        break;
                }
                return tmp;
            }

            move turn(lexicon::direction::type dir) const
            {
                move tmp(*this);
                tmp.direction = dir;
                tmp.start = lexicon::point(actual.x, actual.y);
                tmp.actual = lexicon::point(start.x, start.y);
                tmp.node = node.find('>');
                return tmp;
            }
        };
    }
    void scrawble::search(int x, int y, const std::vector<tile> &rack, const std::set<lexicon::move> &pool)
    {
        node root;

        if (x < 0 || x >= board::size || y < 0 || y >= board::size) {
            return;
        }

        if (board_[x][y + 1] != tile::EMPTY || board_[x][y - 1] != tile::EMPTY ||
            (board_[x][y] != tile::EMPTY && board_[x + 1][y] == tile::EMPTY)) {
            root = dictionary_.reverse();
            recurse_left_right(pool, root, x, y, rack);
        }

        if (board_[x + 1][y] != tile::EMPTY || board_[x - 1][y] != tile::EMPTY ||
            (board_[x][y] != tile::EMPTY && board_[x][y + 1] == tile::EMPTY)) {
            root = dictionary_.reverse();
            recurse_up_down(pool, root, x, y, rack);
        }
    }

    void scrawble::recurse_left_right(const std::set<lexicon::move> &pool, const lexicon::node &root, int x, int y,
                                      const std::vector<tile> &rack)
    {
        if (x < 0 || x >= board::size || y < 0 || y >= board::size) {
            return;
        }

        std::string s;

        int actual = x;

        while (board_[actual][y] != tile::EMPTY) {
            root = root.find(board_[actual][y]);
            s = std::to_string(board_[actual][y]) + s;
            actual--;
        }

        temp::move tmp(lexicon::point(x, y), lexicon::point(actual + 1, y), direction::left, s, root, rack);

        search_recursive(pool, tmp);
    }

    void scrawble::recurse_up_down(const std::set<lexicon::move> &pool, const lexicon::node &root, int x, int y,
                                   const std::vector<tile> &rack)
    {
        if (x < 0 || x >= board::size || y < 0 || y >= board::size) {
            return;
        }

        std::string s;

        int actual = y;

        while (board_[x][actual] != tile::EMPTY) {
            root = root.find(board_[x][actual]);
            s = std::to_string(board_[actual][y]) + s;
            actual--;
        }

        temp::move tmp(lexicon::point(x, y), lexicon::point(x, actual + 1), direction::up, s, root, rack);

        search_recursive(pool, tmp);
    }

    void scrawble::search_recursive(const std::set<move> &pool, const temp::move &m)
    {
        if (!cross(m, m.node.letter)) {
            return;
        }

        if (m.node.marked()) {
            pool.insert(m.convert());
        }

        if (m.node.find(tile::DIRSYM)) {
            if (m.direction == direction::left) {
                search_recursive(pool, m.turn(direction::right));
            } else {
                search_recursive(pool, m.turn(direction::down));
            }
        }

        if (end_of_board(m)) {
            return;
        }

        auto letter = next_tile(m);

        if (letter != tile::EMPTY) {
            if (m.node.find(letter)) {
                search_recursive(pool, m.copy(letter));
            }
        } else {
            for (auto tile : m.rack) {
                if (m.node.find(tile.letter)) {
                    search_recursive(pool, m.copy(tile.letter));
                }
            }
        }
    }

    void scrawble::end_of_board(const temp::move &m)
    {
        switch (move.direction) {
            case direction::left:
                return m.actual.x - 1 < 0;
            case direction::right:
                return m.actual.x + 1 > board::size;
            case direction::up:
                return m.actual.y - 1 < 0;
            case direction::down:
                return m.actual.y + 1 > board::size;
        }
    }

    char scrawble::next_tile(const temp::move &m)
    {
        switch (m.direction) {
            case direction::left:
                return board_[m.actual.x - 1][m.actual.y];
            case direction::right:
                return board_[m.actual.x + 1][m.actual.y];
            case direction::up:
                return board_[m.actual.x][m.actual.y - 1];
            case direction::down:
                return board_[m.actual.x][m.actual.y + 1];
        }
    }
}
