#include <scrawble/board.h>
#include <scrawble/lexicon/node.h>
#include <exception>

namespace scrawble
{
    board::board()
    {
    }

    void board::initialize()
    {
        for (int j = 0; j < size; j++) {
            for (int i = 0; i < size; i++) {
                values_[i][j] = lexicon::node::EMPTY;
                wordBonus_[i][j] = 1;
                letterBonus_[i][j] = 1;
            }
        }

        typedef std::vector<std::array<short, 2>> initializer;

        initializer tripleW = {{0, 0}, {7, 0}, {14, 0}, {0, 7}, {7, 14}, {0, 14}, {14, 0}, {14, 7}, {14, 14}};

        initializer doubleW = {{1, 1},  {2, 2},  {3, 3},  {4, 4},  {7, 7},   {13, 1},  {12, 2},  {11, 3}, {10, 4},
                               {4, 10}, {3, 11}, {2, 12}, {1, 13}, {10, 10}, {11, 11}, {12, 12}, {13, 13}};

        initializer tripleCh = {{5, 1}, {9, 1}, {5, 5},  {9, 5},  {1, 5}, {13, 5},
                                {5, 9}, {9, 9}, {5, 13}, {9, 13}, {1, 9}, {13, 9}};

        initializer doubleCh = {{3, 0}, {11, 0}, {6, 6}, {8, 6}, {6, 8},  {8, 8},  {3, 14}, {11, 14}, {2, 6},  {3, 7},
                                {2, 8}, {6, 2},  {7, 3}, {8, 2}, {11, 7}, {12, 6}, {12, 8}, {6, 12},  {7, 11}, {8, 12}};

        auto loader = [&](short to[size][size], const initializer::iterator& start, const initializer::iterator& end,
                          short what2) {
            for (auto it = start; it != end; ++it) {
                auto pair = *it;
                to[pair[0]][pair[1]] = what2;
            }
        };

        loader(wordBonus_, tripleW.begin(), tripleW.end(), 3);
        loader(wordBonus_, doubleW.begin(), doubleW.end(), 2);
        loader(letterBonus_, tripleCh.begin(), tripleCh.end(), 3);
        loader(letterBonus_, doubleCh.begin(), doubleCh.end(), 2);
    }

    char board::value(int x, int y)
    {
        return values_[x][y];
    }

    short board::bonus(int x, int y, bool word)
    {
        return word ? wordBonus_[x][y] : letterBonus_[x][y];
    }

    board::row board::operator[](int index) const
    {
        if (index < 0 || index >= size) {
            throw std::out_of_range("invalid index for board");
        }
        return board::row(values_[index]);
    }

    board::row::row(char const value[size])
    {
        for (int i = 0; i < size; i++) {
            values_[i] = value[i];
        }
    }

    char board::row::operator[](int index) const
    {
        if (index < 0 || index >= size) {
            throw std::out_of_range("invalid index for board row");
        }
        return values_[index];
    }
}
