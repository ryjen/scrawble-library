#ifndef SCRAWBLE_ALGORITHM_H
#define SCRAWBLE_ALGORITHM_H

namespace scrawble {
    class Algorithm {
       public:
        virtual std::vector<move> randomPlacement(const Board &board, const Rack &rack) = 0;
        virtual std::vector<move> longestPlacement(const Board &board, const Rack &rack) = 0;
        virtual std::vector<move> calculateHighestScorePlacement(const Board &board, const Rack &rack) = 0;
    };
}  // namespace scrawble

#endif
