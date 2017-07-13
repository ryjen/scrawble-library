#ifndef SCRAWBLE_GADDAG_H
#define SCRAWBLE_GADDAG_H

#include <scrawble/board.h>
#include <scrawble/core/move.h>
#include <scrawble/core/trie.h>
#include <scrawble/core/trie_factory.h>
#include <scrawble/rack.h>
#include <algorithm>
#include <random>

namespace scrawble
{
    class Gaddag
    {
        // used to generate random bool values
       private:
        Trie::Ptr trie_;

        /**
         * Passed to some methods to indicate which direction to place tiles while the algorithm is performing
         * processing.
         *
         * @author Matt Sidesinger
         */
       protected:
        typedef struct Direction {
            int xInc;
            int yInc;

            /**
             * @param xInc
             *            When moving in this direction, how X will be incremented to move to the next position.
             * @param yInc
             *            When moving in this direction, how Y will be incremented to move to the next position.
             */
            Direction(int xInc, int yInc) : xInc(xInc), yInc(yInc)
            {
            }

            /**
             * Obtains the next X coordinate in this direction given the current X coordinate.
             * <p>
             * There is no bounds checking in place. hasNext should be called first.
             *
             * @param x     The current X coordinate.
             *
             * @return The next X coordinate in this direction.
             */
            int nextX(int x) const
            {
                return x + xInc;
            }

            /**
             * Obtains the next Y coordinate in this direction given the current Y coordinate.
             * <p>
             * There is no bounds checking in place. hasNext should be called first.
             *
             * @param y
             *            The current Y coordinate.
             *
             * @return The next Y coordinate in this direction.
             */
            int nextY(int y) const
            {
                return y + yInc;
            }

            Direction inverse() const
            {
                if (xInc == 0) {
                    return yInc == -1 ? DOWN : UP;
                } else {
                    return xInc == -1 ? RIGHT : LEFT;
                }
            }

            Direction perpendicular() const
            {
                if (xInc == 0) {
                    return RIGHT;
                } else {
                    return DOWN;
                }
            }

            /**
             * Obtains the next tile in this direction given the current X, Y coordinates on the Board.
             * <p>
             * If the next coordinates do not exist, then <code>null</code> is returned.
             *
             * @param b
             *            The Board that is currently being worked on.
             * @param x
             *            The current X coordinate.
             * @param y
             *            The current Y coordinate.
             *
             * @return <code>true</code> if processing can continue in this direction, <code>false</code> otherwise.
             */
            bool hasNext(const Board &b, int x, int y)
            {
                return b.contains(nextX(x), nextY(y));
            }

            /**
             * Determines whether processing can continue in this direction given the current X, Y coordinates on the
             * Board.
             *
             * @param b
             *            The Board that is currently being worked on.
             * @param x
             *            The current X coordinate.
             * @param y
             *            The current Y coordinate.
             *
             * @return <code>true</code> if processing can continue in this direction, <code>false</code> otherwise.
             */
            bool nextIsInBounds(const Board &b, int x, int y)
            {
                int nx = nextX(x);
                int ny = nextY(y);
                return (1 <= nx && nx <= b.width()) && (1 <= ny && ny <= b.height());
            }
        } Direction;

        constexpr static const Direction UP(0, -1);
        constexpr static const Direction DOWN(0, 1);
        constexpr static const Direction LEFT(-1, 0);
        constexpr static const Direction RIGHT(1, 0);

       public:
        Gaddag(const TrieFactory &trieFactory)
        {
            setTrie(trieFactory.createTrie());
        }

        std::list<Move> randomPlacement(const Board &board, const Rack &rack)
        {
            assert(!rack.empty());

            std::vector<std::list<Move>> allPlacements;
            std::list<Move> randomPlacement;
            std::list<Move> placements;

            if (board.empty()) {
                int x = 0;
                int y = 0;
                // go horizontal
                auto tempPlacements =
                    generateAllPlacements(board, x, y, x, y, rack, placements, trie_->getRoot(), RIGHT);
                allPlacements.insert(allPlacements.end(), tempPlacements.begin(), tempPlacements.end());
            } else {
                int width = board.width();
                int height = board.height();

                for (int x = 1; x <= width; x++) {
                    for (int y = 1; y <= height; y++) {
                        // Is this an empty space?
                        if (!board.contains(x, y)) {
                            // Is there a tile to the East?
                            if (x < width && board.contains(x + 1, y)) {
                                // go horizontal
                                auto tempPlacements =
                                    generateAllPlacements(board, x, y, x, y, rack, placements, trie_->getRoot(), RIGHT);
                                allPlacements.insert(allPlacements.begin(), tempPlacements.begin(),
                                                     tempPlacements.end());
                            }

                            // Is there a tile to the South?
                            if (y < height && board.contains(x, y + 1)) {
                                // go vertical
                                auto tempPlacements =
                                    generateAllPlacements(board, x, y, x, y, rack, placements, trie_->getRoot(), DOWN);
                                allPlacements.insert(allPlacements.begin(), tempPlacements.begin(),
                                                     tempPlacements.end());
                            }
                        }

                    }  // ~for y
                }      // ~for x
            }

            if (allPlacements.size() > 0) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<int> distribution(0, allPlacements.size());
                randomPlacement = allPlacements.at(distribution(gen));
            }

            return randomPlacement;
        }

        std::list<Move> longestPlacement(const Board &board, const Rack &rack)
        {
            assert(!rack.empty());

            std::vector<std::list<Move>> allPlacements;
            std::list<Move> longestPlacement;
            std::list<Move> placements;

            if (board.empty()) {
                int x = 0;
                int y = 0;
                // go horizontal
                auto tempPlacements =
                    generateAllPlacements(board, x, y, x, y, rack, placements, trie_->getRoot(), RIGHT);
                allPlacements.insert(allPlacements.begin(), tempPlacements.begin(), tempPlacements.end());

            } else {
                int width = board.width();
                int height = board.height();

                for (int x = 1; x <= width; x++) {
                    for (int y = 1; y <= height; y++) {
                        // Is this an empty space?
                        if (!board.contains(x, y)) {
                            // Is there a tile to the East?
                            if (x < width && board.contains(x + 1, y)) {
                                // go horizontal
                                auto tempPlacements =
                                    generateAllPlacements(board, x, y, x, y, rack, placements, trie_->getRoot(), RIGHT);
                                allPlacements.insert(allPlacements.begin(), tempPlacements.begin(),
                                                     tempPlacements.end());
                            }

                            // Is there a tile to the South?
                            if (y < height && board.contains(x, y + 1)) {
                                // go vertical
                                auto tempPlacements =
                                    generateAllPlacements(board, x, y, x, y, rack, placements, trie_->getRoot(), DOWN);
                                allPlacements.insert(allPlacements.begin(), tempPlacements.begin(),
                                                     tempPlacements.end());
                            }
                        }

                    }  // ~for y
                }      // ~for x
            }

            if (allPlacements.size() > 0) {
                std::sort(allPlacements.begin(), allPlacements.end(),
                          [](const std::list<Move> &o1, const std::list<Move> &o2) { return (o2.size() - o1.size()); });
                longestPlacement = allPlacements.at(0);
            }

            return longestPlacement;
        }

        std::vector<std::list<Move>> generateAllPlacements(const Board &board, int startX, int startY, int x, int y,
                                                           Rack rack, std::list<Move> &placements,
                                                           const Node::Ptr &node, Direction direction)
        {
            std::vector<std::list<Move>> allPlacements;

            // check prerequisites
            if (!board.contains(x, y)) {
                int currentNumberOfPlacements = placements.size();
                int rackCount = rack.count();

                if (rackCount > 0) {
                    // take the Tile at the beginning of the Rack
                    Tile::Ptr toPlace = rack.pop();
                    if (toPlace->blank()) {
                        toPlace->setLetter('a');
                    }

                    Node::Ptr childNode;
                    // Cycle through the rack taking the first tile and adding it to the end until all tiles on the rack
                    // have been processed.
                    int i = 0;
                    while (true) {
                        childNode = node->getChildNode(toPlace->letter());

                        if (childNode != nullptr && validateCrossWordExists(board, x, y, toPlace, direction)) {
                            if (toPlace.blank()) {
                                // a copy must be placed as the tile placement since toPlace is being modified each
                                // iteration
                                placements.emplace(x, y, std::make_shared<BlankTile>(toPlace.letter()));
                            } else {
                                placements.emplace(x, y, toPlace);
                            }

                            // Is this the end of the word?
                            if (childNode->isTerminal() && !direction.hasNext(board, x, y)) {
                                // Make sure that letters in front of the start position have been considered
                                if (direction == LEFT || direction == UP ||
                                    ((direction == RIGHT || direction == DOWN) &&
                                     !direction.inverse().hasNext(board, startX, startY))) {
                                    std::list<Move> tempPlacements(placements);  // copy
                                    allPlacements.add(tempPlacements);
                                }
                            }

                            std::vector<std::list<Move>> tempAllPlacements;
                            if (direction.nextIsInBounds(board, x, y)) {
                                tempAllPlacements =
                                    generateAllPlacements(board, startX, startY, direction.nextX(x), direction.nextY(y),
                                                          rack, placements, childNode, direction);
                            } else {
                                // Have to switch directions if we want to keep going...
                                // To switch direction we need a cross anchor node.
                                Node::Ptr crossAnchorNode = childNode.getCrossAnchorNode();
                                if (crossAnchorNode != nullptr) {
                                    // switch directions
                                    Direction inverse = InverseDirection[direction];
                                    if (inverse.nextIsInBounds(board, startX, startY)) {
                                        tempAllPlacements = generateAllPlacements(
                                            board, startX, startY, inverse.nextX(startX), inverse.nextY(startY), rack,
                                            placements, crossAnchorNode, inverse);
                                    }
                                }
                            }

                            if (tempAllPlacements.size() > 0) {
                                allPlacements.insert(allPlacements.begin(), tempAllPlacements.begin(),
                                                     tempAllPlacements.end());
                            }

                            // remove any placements that were added
                            while (placements.size() > currentNumberOfPlacements) {
                                placements.removeLast();
                            }
                        }  // childNode != null`

                        // If this is a blank tile, the move to the tile?
                        if (toPlace->blank()) {
                            if (toPlace->letter() < 'z') {
                                // increment the letter
                                toPlace.setLetter((char)(toPlace.letter() + 1));
                                // Don't move to the next tile yet
                                continue;
                            }
                        }

                        // add the tile back to the end of the Rack
                        try {
                            if (toPlace.blank()) {
                                rack.add(std::make_shared<BlankTile>());
                            } else {
                                rack.add(toPlace);
                            }
                        } catch (RackFullException e) {
                            placements.clear();
                            throw std::logic_error("Not expecting RackFullException");
                        }

                        // move to the next tile
                        i++;
                        if (i >= rackCount) {
                            break;
                        }

                        // get the next tile from the rack
                        toPlace = rack.pop();
                        if (toPlace->blank()) {
                            toPlace->setLetter('a');
                        }

                    }  // while (true)
                }

                // what about #? - at least one tile needs to have have been placed
                if (currentNumberOfPlacements > 0) {
                    Node::Ptr crossAnchorNode = node->getCrossAnchorNode();
                    if (crossAnchorNode != nullptr && !direction.hasNext(board, x, y)) {
                        // switch directions
                        Direction inverse = InverseDirection[direction];
                        if (inverse.nextIsInBounds(board, startX, startY)) {
                            std::list<Move> tempPlacements(placements);
                            auto tempAllPlacements = generateAllPlacements(board, startX, startY, inverse.nextX(startX),
                                                                           inverse.nextY(startY), rack, tempPlacements,
                                                                           crossAnchorNode, inverse);

                            if (tempAllPlacements.size() > 0) {
                                allPlacements.insert(allPlacements.begin(), tempAllPlacements.begin(),
                                                     tempAllPlacements.end());
                            }
                        }
                    }
                }

            } else {
                // Does the tile at this location work?
                if (node == nullptr) {
                    return {};
                }
                auto childNode = node.getChildNode(tile.getLetter());
                if (childNode != nullptr) {
                    // Is this the end of the word?
                    if (childNode->isTerminal() && !direction.hasNext(board, x, y)) {
                        // Make sure that letters in front of the start position have been considered
                        if (direction == Direction.LEFT || direction == Direction.UP ||
                            ((direction == Direction.RIGHT || direction == Direction.DOWN) &&
                             !direction.inverse().hasNext(board, startX, startY))) {
                            if (allPlacements == nullptr) {
                                allPlacements = new ArrayList<LinkedList<TilePlacement>>();
                            }
                            auto tempPlacements = placements;  // copy
                            allPlacements.insert(allPlacements.begin(), tempPlacements.begin(), tempPlacements.end());
                        }
                    }

                    // continue down this path...
                    std::vector<std::list<Move>> tempAllPlacements;
                    std::list<Move> tempPlacements;
                    if (direction.nextIsInBounds(board, x, y)) {
                        tempPlacements = placements;
                        tempAllPlacements =
                            generateAllPlacements(board, startX, startY, direction.nextX(x), direction.nextY(y), rack,
                                                  tempPlacements, childNode, direction);
                    } else {
                        // Have to switch directions if we want to keep going...
                        // To switch direction we need a cross anchor node.
                        auto crossAnchorNode = childNode.getCrossAnchorNode();
                        if (crossAnchorNode != nullptr) {
                            // switch directions
                            Direction inverse = direction.inverse();
                            if (inverse.nextIsInBounds(board, startX, startY)) {
                                tempPlacements = placements;
                                tempAllPlacements = generateAllPlacements(board, startX, startY, inverse.nextX(startX),
                                                                          inverse.nextY(startY), rack, tempPlacements,
                                                                          crossAnchorNode, inverse);
                            }
                        }
                    }

                    if (tempAllPlacements != nullptr && tempAllPlacements.size() > 0) {
                        allPlacements.insert(allPlacements.begin(), tempAllPlacements.begin(), tempAllPlacements.end());
                    }
                }  // childNode != null
            }

            return allPlacements;
        }

        std::list<Move> calculateHighestScorePlacement(const Board &board, const Rack &rack)
        {
            assert(!rack.empty());

            std::vector<Move> maxPlacement;
            int maxScore = 0;

            std::list<Move> placements;

            if (board.empty()) {
                int x = 0;
                int y = 0;
                // go horizontal
                maxScore = calculateHighestScorePlacement(board, x, y, x, y, rack, placements, trie.getRoot(), RIGHT);
                if (maxScore > 0) {
                    maxPlacement = placements;
                }

            } else {
                int width = board.width();
                int height = board.height();
                int score = 0;

                for (int x = 1; x <= width; x++) {
                    for (int y = 1; y <= height; y++) {
                        // Is this an empty space?
                        if (!board.contains(x, y)) {
                            // Is there a tile to the East?
                            if (x < width && board.contains(x + 1, y)) {
                                // go horizontal
                                placements.clear();
                                score = calculateHighestScorePlacement(board, x, y, x, y, rack, placements,
                                                                       trie.getRoot(), RIGHT);
                                if (score > maxScore) {
                                    maxScore = score;
                                    maxPlacement = placements;  // copy
                                }
                            }

                            // Is there a tile to the South?
                            if (y < height && board.contains(x, y + 1)) {
                                // go vertical
                                placements.clear();
                                score = calculateHighestScorePlacement(board, x, y, x, y, rack, placements,
                                                                       trie.getRoot(), DOWN);
                                if (score > maxScore) {
                                    maxScore = score;
                                    maxPlacement = placements;  // copy
                                }
                            }
                        }

                    }  // ~for y
                }      // ~for x
            }

            return maxPlacement;
        }

        int calculateHighestScorePlacement(const Board &board, int startX, int startY, int x, int y, const Rack &rack,
                                           const std::list<Move> &placements, const Node::Ptr &node,
                                           Direction direction)
        {
            int maxScore = 0;
            int tempScore = 0;
            std::vector<Move> maxPlacement;

            // Is the current location empty?
            Tile tile = board[x][y];
            // check prerequisites
            if (tile.empty()) {
                int currentNumberOfPlacements = placements.size();
                int rackCount = rack.tileCount();

                if (rackCount > 0) {
                    // take the Tile at the beginning of the Rack
                    Tile toPlace = rack.take();
                    if (toPlace.isBlankTile()) {
                        BlankTile.setLetter(((BlankTile)toPlace), 'a');
                    }

                    Node::Ptr childNode;
                    // Cycle through the rack taking the first tile and adding it to the end until all tiles on the rack
                    // have been processed.
                    int i = 0;
                    while (true) {
                        childNode = node->getChildNode(toPlace.getLetter());

                        if (childNode != nullptr && validateCrossWordExists(board, x, y, toPlace, direction)) {
                            placements.emplace(x, y, toPlace);

                            // Is this the end of the word?
                            if (childNode.isTerminal() && !direction.hasNext(board, x, y)) {
                                // Make sure that letters in front of the start position have been considered
                                if (direction == Direction.LEFT || direction == Direction.UP ||
                                    ((direction == Direction.RIGHT || direction == Direction.DOWN) &&
                                     !direction.inverse().hasNext(board, startX, startY))) {
                                    // score the current placement
                                    tempScore = board.score(placements, false);
                                    if ((tempScore > maxScore) ||
                                        (tempScore > 0 && tempScore == maxScore && RANDOM.nextBoolean())) {
                                        maxScore = tempScore;
                                        // copy placements to the max placement place holder
                                        maxPlacement = placements;
                                    }
                                }
                            }

                            if (direction.nextIsInBounds(board, x, y)) {
                                tempScore = calculateHighestScorePlacement(board, startX, startY, direction.nextX(x),
                                                                           direction.nextY(y), rack, placements,
                                                                           childNode, direction);
                            } else {
                                // Have to switch directions if we want to keep going...
                                // To switch direction we need a cross anchor node.
                                auto crossAnchorNode = childNode.getCrossAnchorNode();
                                if (crossAnchorNode != nullptr) {
                                    // switch directions
                                    Direction inverse = direction.inverse();
                                    if (inverse.nextIsInBounds(board, startX, startY)) {
                                        tempScore = calculateHighestScorePlacement(
                                            board, startX, startY, inverse.nextX(startX), inverse.nextY(startY), rack,
                                            placements, crossAnchorNode, inverse);
                                    }
                                }
                            }

                            if ((tempScore > maxScore) ||
                                (tempScore > 0 && tempScore == maxScore && RANDOM.nextBoolean())) {
                                maxScore = tempScore;
                                maxPlacement = placements;
                            }

                            // remove any placements that were added
                            while (placements.size() > currentNumberOfPlacements) {
                                placements.removeLast();
                            }
                        }  // childNode != null`

                        // If this is a blank tile, the move to the tile?
                        if (toPlace.blank()) {
                            if (toPlace.getLetter() < 'z') {
                                // increment the letter
                                BlankTile.setLetter(((BlankTile)toPlace), (char)(toPlace.getLetter() + 1));
                                // Don't move to the next tile yet
                                continue;
                            }
                        }

                        // add the tile back to the end of the Rack
                        try {
                            if (toPlace.isBlankTile()) {
                                rack.add(new BlankTile());
                            } else {
                                rack.add(toPlace);
                            }
                        } catch (RackFullException e) {
                            placements.clear();
                            throw new RuntimeException("Not expecting RackFullException", e);
                        }

                        // move to the next tile
                        i++;
                        if (i >= rackCount) {
                            break;
                        }

                        // get the next tile from the rack
                        toPlace = rack.take();
                        if (toPlace.isBlankTile()) {
                            BlankTile.setLetter(((BlankTile)toPlace), 'a');
                        }

                    }  // while (true)
                }

                // what about #? - at least one tile needs to have have been placed
                if (currentNumberOfPlacements > 0) {
                    TrieNode crossAnchorNode = node.getCrossAnchorNode();
                    if (crossAnchorNode != null && !direction.hasNext(board, x, y)) {
                        // switch directions
                        Direction inverse = direction.inverse();
                        if (inverse.nextIsInBounds(board, startX, startY)) {
                            LinkedList<TilePlacement> tempPlacements = new LinkedList<TilePlacement>(placements);
                            tempScore = calculateHighestScorePlacement(board, startX, startY, inverse.nextX(startX),
                                                                       inverse.nextY(startY), rack, tempPlacements,
                                                                       crossAnchorNode, inverse);
                            if ((tempScore > maxScore) ||
                                (tempScore > 0 && tempScore == maxScore && RANDOM.nextBoolean())) {
                                maxScore = tempScore;
                                // copy tempPlacements to the max placement place holder
                                if (maxPlacement == null) {
                                    maxPlacement = new ArrayList<TilePlacement>(tempPlacements);
                                } else {
                                    maxPlacement.clear();
                                    maxPlacement.addAll(tempPlacements);
                                }
                            }
                        }
                    }
                }

            } else {
                // Does the tile at this location work?
                if (node == nullptr || tile.empty()) {
                    return 0;
                }
                auto childNode = node->getChildNode(tile.getLetter());
                if (childNode != nullptr) {
                    // Is this the end of the word?
                    if (childNode.isTerminal() && !direction.hasNext(board, x, y)) {
                        // Make sure that letters in front of the start position have been considered
                        if (direction == Direction.LEFT || direction == Direction.UP ||
                            ((direction == Direction.RIGHT || direction == Direction.DOWN) &&
                             !direction.inverse().hasNext(board, startX, startY))) {
                            // score the current placement
                            maxScore = board.score(placements, false);
                            // copy placements to the max placement place holder
                            maxPlacement = placements;
                        }
                    }

                    // continue down this path...
                    std::list<Move> tempPlacements;
                    if (direction.nextIsInBounds(board, x, y)) {
                        tempPlacements = placements;
                        tempScore = calculateHighestScorePlacement(board, startX, startY, direction.nextX(x),
                                                                   direction.nextY(y), rack, tempPlacements, childNode,
                                                                   direction);
                    } else {
                        // Have to switch directions if we want to keep going...
                        // To switch direction we need a cross anchor node.
                        auto crossAnchorNode = childNode.getCrossAnchorNode();
                        if (crossAnchorNode != nullptr) {
                            // switch directions
                            Direction inverse = direction.inverse();
                            if (inverse.nextIsInBounds(board, startX, startY)) {
                                tempPlacements = placements;
                                tempScore = calculateHighestScorePlacement(board, startX, startY, inverse.nextX(startX),
                                                                           inverse.nextY(startY), rack, tempPlacements,
                                                                           crossAnchorNode, inverse);
                            }
                        }
                    }

                    if ((tempScore > maxScore) || (tempScore > 0 && tempScore == maxScore && RANDOM.nextBoolean())) {
                        maxScore = tempScore;
                        // copy tempPlacements to the max placement place holder
                        maxPlacement = tempPlacements;
                    }
                }  // childNode != null
            }

            if (!maxPlacement.empty() && maxPlacement.size() > 0) {
                placements.clear();
                placements.addAll(maxPlacement);
            }

            return maxScore;
        }

        /**
         * Determines whether the word created perpendicular to the given direction by placing the tile
         * at the x,y coordinates is valid.
         *
         * @param board     The board where the existing tile have been placed on
         * @param startX    The x coordinate where the tile is being placed
         * @param startY    The y coordinate where the tile is being placed
         * @param toPlace   The tile that is being placed
         * @param direction The direction perpendicular to the direction to check
         *
         * @return      <code>true</code> if the perpendicular word is valid, otherwise </code>false</code.
         */
        bool validateCrossWordExists(const Board &board, int startX, int startY, const Tile &toPlace,
                                     Direction direction)
        {
            bool exists = false;

            Direction d = direction.perpendicular();
            if (!d.hasNext(board, startX, startY) && !d.inverse().hasNext(board, startX, startY)) {
                exists = true;
            } else {
                Tile tile = toPlace;
                TrieNode node = trie.getRoot();
                int x = startX;
                int y = startY;

                while (tile != null) {
                    node = node.getChildNode(tile.getLetter());
                    if (node == null) {
                        // this word is not valid - there should be a node for every child
                        break;
                    }

                    if (d.hasNext(board, x, y)) {
                        x = d.nextX(x);
                        y = d.nextY(y);
                        tile = board.get(x, y);
                    } else {
                        d = d.inverse();
                        if (!d.hasNext(board, startX, startY)) {
                            break;
                        }

                        x = d.nextX(startX);
                        y = d.nextY(startY);
                        tile = board.get(x, y);

                        if (tile != null) {
                            // must consume a cross anchor node
                            node = node.getCrossAnchorNode();
                            if (node == null) {
                                break;
                            }
                        }
                    }
                }  // ~while

                if (node != null) {
                    exists = node.isTerminal();
                }
            }

            return exists;
        }

        Trie::Ptr getTrie() const
        {
            return trie_;
        }

        void setTrie(const Trie::Ptr &trie)
        {
            trie_ = trie;
        }
    };
}  // namespace scrawble
