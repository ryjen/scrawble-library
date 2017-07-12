#include <scrawble/board.h>
#include <exception>

namespace scrawble {
    Board::Board() {
        init();
    }

    Board::Board(const Board& other) {
        copy(other);
    }

    Board::Board(Board&& other) {
        copy(other);
    }

    Board::~Board() {
    }

    Board& Board::operator=(const Board& other) {
        copy(other);
        return *this;
    }

    Board& Board::operator=(Board&& other) {
        copy(other);
        return *this;
    }

    void Board::copy(const Board& other) {
        for (int j = 0; j < size; j++) {
            for (int i = 0; i < size; i++) {
                values_[i][j] = other.values_[i][j];
                wordBonus_[i][j] = other.wordBonus_[i][j];
                letterBonus_[i][j] = other.letterBonus_[i][j];
            }
        }
    }

    void Board::init() {
        for (int j = 0; j < size; j++) {
            for (int i = 0; i < size; i++) {
                values_[i][j] = Tile();
                wordBonus_[i][j] = 1;
                letterBonus_[i][j] = 1;
            }
        }

        typedef std::vector<std::array<short, 2>> initializer;

        initializer tripleW = {{{0, 0}},  {{7, 0}},  {{14, 0}}, {{0, 7}},  {{7, 14}},
                               {{0, 14}}, {{14, 0}}, {{14, 7}}, {{14, 14}}};

        initializer doubleW = {{{1, 1}},  {{2, 2}},   {{3, 3}},   {{4, 4}},   {{7, 7}},  {{13, 1}},
                               {{12, 2}}, {{11, 3}},  {{10, 4}},  {{4, 10}},  {{3, 11}}, {{2, 12}},
                               {{1, 13}}, {{10, 10}}, {{11, 11}}, {{12, 12}}, {{13, 13}}};

        initializer tripleCh = {{{5, 1}}, {{9, 1}}, {{5, 5}},  {{9, 5}},  {{1, 5}}, {{13, 5}},
                                {{5, 9}}, {{9, 9}}, {{5, 13}}, {{9, 13}}, {{1, 9}}, {{13, 9}}};

        initializer doubleCh = {{{3, 0}},   {{11, 0}}, {{6, 6}},  {{8, 6}},  {{6, 8}},  {{8, 8}}, {{3, 14}},
                                {{11, 14}}, {{2, 6}},  {{3, 7}},  {{2, 8}},  {{6, 2}},  {{7, 3}}, {{8, 2}},
                                {{11, 7}},  {{12, 6}}, {{12, 8}}, {{6, 12}}, {{7, 11}}, {{8, 12}}};

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

    bool Board::contains(int x, int y) const {
        try {
            return !operator[](x)[y].empty();
        } catch (const std::out_of_range& e) {
            return false;
        }
    }

    int Board::width() const {
        return size;
    }

    int Board::height() const {
        return size;
    }

    bool Board::empty() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (!values_[i][j].empty()) {
                    return false;
                }
            }
        }
        return true;
    }

    Tile& Board::value(int x, int y) {
        return values_[x][y];
    }

    short Board::bonus(int x, int y, bool word) {
        return word ? wordBonus_[x][y] : letterBonus_[x][y];
    }

    Board::Row Board::operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("invalid index for board");
        }
        Tile const* row_values = values_[index];

        return Board::Row(row_values);
    }

    Board::Row::Row(Tile const value[size]) {
        for (int i = 0; i < size; i++) {
            values_[i] = value[i];
        }
    }

    Board::Row::Row(const Row& other) {
        for (int i = 0; i < size; i++) {
            values_[i] = other.values_[i];
        }
    }

    Tile Board::Row::operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("invalid index for board row");
        }
        return values_[index];
    }

    Tile Board::place(int x, int y, const Tile& value) {
        if (x < 0 || x >= size || y < 0 || y >= size) {
            throw std::out_of_range("invalid index for board place");
        }

        auto existing = values_[x][y];

        values_[x][y] = value;

        return existing;
    }

    Board& Board::reset(int x, int y) {
        if (x < 0 || x >= size || y < 0 || y >= size) {
            throw std::out_of_range("invalid index for board place");
        }

        values_[x][y] = Tile();
        return *this;
    }
}  // namespace scrawble
