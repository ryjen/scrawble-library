#ifndef SCRAWBLE_ALGORITHM_H
#define SCRAWBLE_ALGORITHM_H

namespace scrawble
{
    class Algorithm
    {
       public:
        /**
         * Generates a random, but valid list of tile placements for the given Rack and Board.
         *
         * @param board		The board to use.
         * @param rack		The rack to pull tiles from
         *
         * @return	A random list of tile placements
         */
        virtual std::vector<Move> randomPlacement(const Board &board, const Rack &rack) = 0;

        /**
         * Generates the longest list of tile placements for the given Rack and Board.
         *
         * @param board		The board to use.
         * @param rack		The rack to pull tiles from
         *
         * @return	A random and longest list of tile placements
         */
        virtual std::vector<Move> longestPlacement(const Board &board, const Rack &rack) = 0;

        /**
         * Determines the highest score given the current Rack and Board.  The method implementation is not intended
         * to use artificial intelligence  (play-ahead strategy); this type of logic should be implemented in a
         * different method.
         *
         * @param board		The board to use
         * @param rack		The rack to pull tiles from
         *
         * @return		The highest score that this player can attain with the given rack on the current board's
         * 				configuration.
         */
        virtual std::vector<Move> calculateHighestScorePlacement(const Board &board, const Rack &rack) = 0;
    };
}
#endif
