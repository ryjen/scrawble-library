#ifndef SCRAWBLE_BOARD_H
#define SCRAWBLE_BOARD_H

#include <array>
#include <iostream>
#include <iterator>
#include <vector>

class board
{
   public:
    const static int size = 15;

    class column_iterator : public std::iterator<std::forward_iterator_tag, const char>
    {
       public:
        column_iterator(const board &board, int row, int index = 0) : board_(board), row_(row), index_(index)
        {
        }

        bool operator==(const column_iterator &other) const
        {
            return row_ == other.row_ && index_ == other.index_;
        }

        bool operator!=(const column_iterator &other) const
        {
            return !operator==(other);
        }

        reference operator*() const
        {
            return board_.values_[row_][index_];
        }

        pointer operator->() const
        {
            return &board_.values_[row_][index_];
        }

        column_iterator operator++(int)
        {
            column_iterator tmp(*this);
            index_++;
            return tmp;
        }

        column_iterator &operator++()
        {
            index_++;
            return *this;
        }

        column_iterator operator+(difference_type v) const
        {
            return column_iterator(board_, row_, index_ + v);
        }

       private:
        const board &board_;
        int index_;
        const int row_;
    };

    class row_iterator : public std::iterator<std::forward_iterator_tag, const char[size]>
    {
       public:
        typedef column_iterator iterator;
        typedef const column_iterator const_iterator;

        row_iterator(const board &board, int index = 0) : board_(board), index_(index)
        {
        }

        bool operator==(const row_iterator &other) const
        {
            return index_ == other.index_;
        }

        bool operator!=(const row_iterator &other) const
        {
            return !operator==(other);
        }

        reference operator*() const
        {
            return board_.values_[index_];
        }

        pointer operator->() const
        {
            return &board_.values_[index_];
        }

        row_iterator operator++(int)
        {
            row_iterator tmp(*this);
            index_++;
            return tmp;
        }

        row_iterator &operator++()
        {
            index_++;
            return *this;
        }

        row_iterator operator+(difference_type v) const
        {
            return row_iterator(board_, index_ + v);
        }

        const_iterator begin() const
        {
            return const_iterator(board_, index_);
        }

        const_iterator end() const
        {
            return const_iterator(board_, index_, size);
        }

        iterator begin()
        {
            return iterator(board_, index_);
        }

        iterator end()
        {
            return iterator(board_, index_, size);
        }

       private:
        const board &board_;
        int index_;
    };

    typedef row_iterator iterator;
    typedef const row_iterator const_iterator;

    const_iterator begin() const
    {
        return const_iterator(*this);
    }
    const_iterator end() const
    {
        return const_iterator(*this, size);
    }

    iterator begin()
    {
        return iterator(*this);
    }

    iterator end()
    {
        return iterator(*this, size);
    }

    const_iterator cbegin() const
    {
        return const_iterator(*this);
    }
    const_iterator cend() const
    {
        return const_iterator(*this, size);
    }

    board()
    {
        for (int j = 0; j < size; j++) {
            for (int i = 0; i < size; i++) {
                values_[i][j] = '_';
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

        auto loader = [&](short to[size][size], const initializer::iterator &start, const initializer::iterator &end,
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

    void print(std::ostream &out) const
    {
        for (int i = 0; i < size; i++) {
            if (i == 0) {
                out << "╭───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───╮\n";
            } else {
                out << "├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n";
            }
            for (int j = 0; j < size; j++) {
                out << "| ";
                if (values_[i][j] == '_') {
                    out << " ";
                } else {
                    out << values_[i][j];
                }
                out << " ";
            }
            out << "│\n";
        }
        out << "╰───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───╯\n";
    }

   private:
    char values_[size][size];
    short wordBonus_[size][size];
    short letterBonus_[size][size];
};

#endif
