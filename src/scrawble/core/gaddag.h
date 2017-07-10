#ifndef SCRAWBLE_GADDAG_H
#define SCRAWBLE_GADDAG_H

namespace scrawble
{
    class Gaddag
    {
        // used to generate random boolean values
       private:
        Trie::Ptr trie_;

        /**
         * Passed to some methods to indicate which direction to place tiles while the algorithm is performing
         * processing.
         *
         * @author Matt Sidesinger
         */
       protected:
        typedef enum { UP, DOWN, LEFT, RIGHT } Direction;

        static Direction InverseDirection[] = {DOWN, UP, RIGHT, LEFT};
        static Direction PerpendicularDirection[] = {RIGHT, RIGHT, DOWN, DOWN};

        typedef struct Dir {
            int xInc;
            int yInc;

            /**
             * @param xInc
             *            When moving in this direction, how X will be incremented to move to the next position.
             * @param yInc
             *            When moving in this direction, how Y will be incremented to move to the next position.
             */
            Dir(int xInc, int yInc) xInc(xInc), yInc(yInc)
            {
            }

            /**
             * Obtains the next X coordinate in this direction given the current X coordinate.
             * <p>
             * There is no bounds checking in place. hasNext should be called first.
             *
             * @param x		The current X coordinate.
             *
             * @return The next X coordinate in this direction.
             */
            int nextX(int x)
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
            int nextY(int y)
            {
                return y + yInc;
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
            bool nextIsInBounds(int x, int y)
            {
                int nextX = nextX(x);
                int nextY = nextY(y);
                return (1 <= nextX && nextX <= Board::size) && (1 <= nextY && nextY <= Board::size);
            }
        };

       public:
        Gaddag()
        {
            init(new FileBasedTrieFactory());
        }

        Gaddag(const TrieFactory &trieFactory)
        {
            init(trieFactory);
        }

       protected:
        void init(const TrieFactory &trieFactory)
        {
            setTrie(trieFactory.createTrie());
        }

       public:
        std::vector<Move> randomPlacement(const Board &board, const Rack &rack)
        {
            assert(!rack.isEmpty());

            std::vector<std::list<Move>> allPlacements;
            std::list<Move> randomPlacement;
            std::list<Move> placements;

            if (board.isEmpty()) {
                int x = board.getStartX();
                int y = board.getStartY();
                // go horizontal
                auto tempPlacements =
                    generateAllPlacements(board, x, y, x, y, rack, placements, trie.getRoot(), Direction.RIGHT);
                allPlacements.insert(allPlacements.end(), tempPlacements.begin(), tempPlacements.end());
            } else {
                int width = board.getWidth();
                int height = board.getHeight();

                for (int x = 1; x <= width; x++) {
                    for (int y = 1; y <= height; y++) {
                        // Is this an empty space?
                        if (board[x][y].isEmpty()) {
                            // Is there a tile to the East?
                            if (x < width && !board[x + 1][y].isEmpty()) {
                                // go horizontal
                                auto tempPlacements = generateAllPlacements(board, x, y, x, y, rack, placements,
                                                                            trie.getRoot(), Direction.RIGHT);
                                allPlacements.addAll(tempPlacements);
                            }

                            // Is there a tile to the South?
                            if (y < height && !board[x][y + 1].isEmpty()) {
                                // go vertical
                                auto tempPlacements = generateAllPlacements(board, x, y, x, y, rack, placements,
                                                                            trie.getRoot(), Direction.DOWN);
                                allPlacements.insert(allPlacements.begin(), tempPlacements.begin(),
                                                     tempPlacements.end());
                            }
                        }

                    }  // ~for y
                }      // ~for x
            }

            if (allPlacements.size() > 0) {
                randomPlacement = allPlacements.at(r.nextInt(allPlacements.size()));
            }

            return randomPlacement;
        }

        std::vector<Move> longestPlacement(const Board &board, const Rack &rack)
        {
            assert(!rack.isEmpty());

            std::vector<std::list<Move>> allPlacements;
            std::list<Move> longestPlacement;
            std::list<Move> placements;

            if (board.isEmpty()) {
                int x = board.getStartX();
                int y = board.getStartY();
                // go horizontal
                auto tempPlacements =
                    generateAllPlacements(board, x, y, x, y, rack, placements, trie.getRoot(), Direction.RIGHT);
                allPlacements.insert(allPlacements.begin(), tempPlacements.begin(), tempPlacements.end());

            } else {
                int width = board.getWidth();
                int height = board.getHeight();

                for (int x = 1; x <= width; x++) {
                    for (int y = 1; y <= height; y++) {
                        // Is this an empty space?
                        if (board[x][y].isEmpty()) {
                            // Is there a tile to the East?
                            if (x < width && !board[x + 1][y].isEmpty()) {
                                // go horizontal
                                auto tempPlacements = generateAllPlacements(board, x, y, x, y, rack, placements,
                                                                            trie.getRoot(), Direction.RIGHT);
                                allPlacements.insert(allPlacements.begin(), tempPlacements.begin(),
                                                     tempPlacements.end());
                            }

                            // Is there a tile to the South?
                            if (y < height && !board[x][y + 1].isEmpty()) {
                                // go vertical
                                auto tempPlacements = generateAllPlacements(board, x, y, x, y, rack, placements,
                                                                            trie.getRoot(), Direction.DOWN);
                                allPlacements.insert(allPlacements.begin(), tempPlacements.begin(),
                                                     tempPlacements.end());
                            }
                        }

                    }  // ~for y
                }      // ~for x
            }

            if (allPlacements.size() > 0) {
                std::sort(allPlacements, []](const std::list<<Move> &o1, const std::list<Move> &o2)
                    {
                    return (o2.size() - o1.size());
                    }
                );
                longestPlacement = allPlacements.at(0);
            }

            return longestPlacement;
        }

        std::vector<std::list<Move>> generateAllPlacements(const Board &board, int startX, int startY, int x, int y,
                                                           const Rack &rack, const std::list<Move> &placements,
                                                           const Node::Ptr &node, Direction direction)
        {
            std::vector<std::list<Move>> allPlacements;

            // Is the current location empty?
            Tile tile = board[x][y];

            // check prerequisites
            if (tile.isEmpty()) {
                int currentNumberOfPlacements = placements.size();
                int rackCount = rack.tileCount();

                if (rackCount > 0) {
                    // take the Tile at the beginning of the Rack
                    Tile toPlace = rack.take();
                    if (toPlace.isBlankTile()) {
                        BlankTile.setLetter((toPlace), 'a');
                    }

                    Node::Ptr childNode;
                    // Cycle through the rack taking the first tile and adding it to the end until all tiles on the rack
                    // have been processed.
                    int i = 0;
                    while (true) {
                        childNode = node->getChildNode(toPlace.getLetter());

                        if (childNode != nullptr && validateCrossWordExists(board, x, y, toPlace, direction)) {
                            if (toPlace.isBlankTile()) {
                                // a copy must be placed as the tile placement since toPlace is being modified each
                                // iteration
                                placements.emplace(x, y, new BlankTile(toPlace.getLetter()));
                            } else {
                                placements.emplace(x, y, toPlace);
                            }

                            // Is this the end of the word?
                            if (childNode.isTerminal() && !direction.hasNext(board, x, y)) {
                                // Make sure that letters in front of the start position have been considered
                                if (direction == Direction.LEFT || direction == Direction.UP ||
                                    ((direction == Direction.RIGHT || direction == Direction.DOWN) &&
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
                        if (toPlace.isBlankTile()) {
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
                            if (allPlacements == null) {
                                allPlacements = new ArrayList<LinkedList<TilePlacement>>();
                            }
                            LinkedList<TilePlacement> tempPlacements =
                                new LinkedList<TilePlacement>(placements);  // copy
                            allPlacements.add(tempPlacements);
                        }
                    }

                    // continue down this path...
                    List<LinkedList<TilePlacement>> tempAllPlacements = null;
                    LinkedList<TilePlacement> tempPlacements = null;
                    if (direction.nextIsInBounds(board, x, y)) {
                        tempPlacements = new LinkedList<TilePlacement>(placements);
                        tempAllPlacements =
                            generateAllPlacements(board, startX, startY, direction.nextX(x), direction.nextY(y), rack,
                                                  tempPlacements, childNode, direction);
                    } else {
                        // Have to switch directions if we want to keep going...
                        // To switch direction we need a cross anchor node.
                        TrieNode crossAnchorNode = childNode.getCrossAnchorNode();
                        if (crossAnchorNode != null) {
                            // switch directions
                            Direction inverse = direction.inverse();
                            if (inverse.nextIsInBounds(board, startX, startY)) {
                                tempPlacements = new LinkedList<TilePlacement>(placements);
                                tempAllPlacements = generateAllPlacements(board, startX, startY, inverse.nextX(startX),
                                                                          inverse.nextY(startY), rack, tempPlacements,
                                                                          crossAnchorNode, inverse);
                            }
                        }
                    }

                    if (tempAllPlacements != null && tempAllPlacements.size() > 0) {
                        if (allPlacements == null) {
                            allPlacements = new ArrayList<LinkedList<TilePlacement>>(tempAllPlacements.size());
                        }
                        allPlacements.addAll(tempAllPlacements);
                    }
                }  // childNode != null
            }

            return allPlacements;
        }

        @Override public List<TilePlacement> calculateHighestScorePlacement(final Board board, final Rack rack)
        {
            Validate.notNull(board, "Board cannot be null");
            Validate.notNull(rack, "Rack cannot be null");
            if (rack.isEmpty()) {
                throw new IllegalArgumentException("Rack cannot be empty");
            }

            List<TilePlacement> maxPlacement = null;
            int maxScore = 0;

            LinkedList<TilePlacement> placements = new LinkedList<TilePlacement>();

            if (board.isEmpty()) {
                int x = board.getStartX();
                int y = board.getStartY();
                // go horizontal
                maxScore = calculateHighestScorePlacement(board, x, y, x, y, rack, placements, trie.getRoot(),
                                                          Direction.RIGHT);
                if (maxScore > 0) {
                    maxPlacement = placements;
                }

            } else {
                int width = board.getWidth();
                int height = board.getHeight();
                int score = 0;

                for (int x = 1; x <= width; x++) {
                    for (int y = 1; y <= height; y++) {
                        // Is this an empty space?
                        if (board.get(x, y) == null) {
                            // Is there a tile to the East?
                            if (x < width && board.get(x + 1, y) != null) {
                                // go horizontal
                                placements.clear();
                                score = calculateHighestScorePlacement(board, x, y, x, y, rack, placements,
                                                                       trie.getRoot(), Direction.RIGHT);
                                if (score > maxScore) {
                                    maxScore = score;
                                    maxPlacement = new ArrayList<TilePlacement>(placements);  // copy
                                }
                            }

                            // Is there a tile to the South?
                            if (y < height && board.get(x, y + 1) != null) {
                                // go vertical
                                placements.clear();
                                score = calculateHighestScorePlacement(board, x, y, x, y, rack, placements,
                                                                       trie.getRoot(), Direction.DOWN);
                                if (score > maxScore) {
                                    maxScore = score;
                                    maxPlacement = new ArrayList<TilePlacement>(placements);  // copy
                                }
                            }
                        }

                    }  // ~for y
                }      // ~for x
            }

            return maxPlacement;
        }

       protected
        int calculateHighestScorePlacement(final Board board, final int startX, final int startY, final int x,
                                           final int y, final Rack rack, final LinkedList<TilePlacement> placements,
                                           final TrieNode node, final Direction direction)
        {
            int maxScore = 0;
            int tempScore = 0;
            List<TilePlacement> maxPlacement = null;

            // Is the current location empty?
            Tile tile = board.get(x, y);
            // check prerequisites
            if (tile == null) {
                int currentNumberOfPlacements = placements.size();
                int rackCount = rack.tileCount();

                if (rackCount > 0) {
                    // take the Tile at the beginning of the Rack
                    Tile toPlace = rack.take();
                    if (toPlace.isBlankTile()) {
                        BlankTile.setLetter(((BlankTile)toPlace), 'a');
                    }

                    TrieNode childNode = null;
                    // Cycle through the rack taking the first tile and adding it to the end until all tiles on the rack
                    // have been processed.
                    int i = 0;
                    while (true) {
                        childNode = node.getChildNode(toPlace.getLetter());

                        if (childNode != null && validateCrossWordExists(board, x, y, toPlace, direction)) {
                            if (toPlace.isBlankTile()) {
                                // a copy must be placed as the tile placement since toPlace is being modified each
                                // iteration
                                placements.add(new TilePlacement(x, y, new BlankTile(toPlace.getLetter())));
                            } else {
                                placements.add(new TilePlacement(x, y, toPlace));
                            }

                            // Is this the end of the word?
                            if (childNode.isTerminal() && !direction.hasNext(board, x, y)) {
                                // Make sure that letters in front of the start position have been considered
                                if (direction == Direction.LEFT || direction == Direction.UP ||
                                    ((direction == Direction.RIGHT || direction == Direction.DOWN) &&
                                     !direction.inverse().hasNext(board, startX, startY))) {
                                    // score the current placement
                                    try {
                                        tempScore = board.score(placements, false);
                                        if ((tempScore > maxScore) ||
                                            (tempScore > 0 && tempScore == maxScore && RANDOM.nextBoolean())) {
                                            maxScore = tempScore;
                                            // copy placements to the max placement place holder
                                            if (maxPlacement == null) {
                                                maxPlacement = new ArrayList<TilePlacement>(placements);
                                            } else {
                                                maxPlacement.clear();
                                                maxPlacement.addAll(placements);
                                            }
                                        }
                                    } catch (IllegalTilePlacementException e) {
                                        logger.error("IllegalTilePlacementException during calculation.", e);
                                        logger.error("Board state: {}", board);
                                        logger.error("Tile placements: {}", placements);
                                        // continue
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
                                TrieNode crossAnchorNode = childNode.getCrossAnchorNode();
                                if (crossAnchorNode != null) {
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
                                // copy placements to the max placement place holder
                                if (maxPlacement == null) {
                                    maxPlacement = new ArrayList<TilePlacement>(placements);
                                } else {
                                    maxPlacement.clear();
                                    maxPlacement.addAll(placements);
                                }
                            }

                            // remove any placements that were added
                            while (placements.size() > currentNumberOfPlacements) {
                                placements.removeLast();
                            }
                        }  // childNode != null`

                        // If this is a blank tile, the move to the tile?
                        if (toPlace.isBlankTile()) {
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
                if (node == null || tile == null) {
                    return 0;
                }
                TrieNode childNode = node.getChildNode(tile.getLetter());
                if (childNode != null) {
                    // Is this the end of the word?
                    if (childNode.isTerminal() && !direction.hasNext(board, x, y)) {
                        // Make sure that letters in front of the start position have been considered
                        if (direction == Direction.LEFT || direction == Direction.UP ||
                            ((direction == Direction.RIGHT || direction == Direction.DOWN) &&
                             !direction.inverse().hasNext(board, startX, startY))) {
                            // score the current placement
                            try {
                                maxScore = board.score(placements, false);
                                // copy placements to the max placement place holder
                                maxPlacement = new ArrayList<TilePlacement>(placements);
                            } catch (IllegalTilePlacementException e) {
                                logger.error("IllegalTilePlacementException during calculation.", e);
                                logger.error("Board state: {}", board);
                                logger.error("Tile placements: {}", placements);
                                // continue
                            }
                        }
                    }

                    // continue down this path...
                    LinkedList<TilePlacement> tempPlacements = null;
                    if (direction.nextIsInBounds(board, x, y)) {
                        tempPlacements = new LinkedList<TilePlacement>(placements);
                        tempScore = calculateHighestScorePlacement(board, startX, startY, direction.nextX(x),
                                                                   direction.nextY(y), rack, tempPlacements, childNode,
                                                                   direction);
                    } else {
                        // Have to switch directions if we want to keep going...
                        // To switch direction we need a cross anchor node.
                        TrieNode crossAnchorNode = childNode.getCrossAnchorNode();
                        if (crossAnchorNode != null) {
                            // switch directions
                            Direction inverse = direction.inverse();
                            if (inverse.nextIsInBounds(board, startX, startY)) {
                                tempPlacements = new LinkedList<TilePlacement>(placements);
                                tempScore = calculateHighestScorePlacement(board, startX, startY, inverse.nextX(startX),
                                                                           inverse.nextY(startY), rack, tempPlacements,
                                                                           crossAnchorNode, inverse);
                            }
                        }
                    }

                    if ((tempScore > maxScore) || (tempScore > 0 && tempScore == maxScore && RANDOM.nextBoolean())) {
                        maxScore = tempScore;
                        // copy tempPlacements to the max placement place holder
                        if (maxPlacement == null) {
                            maxPlacement = new ArrayList<TilePlacement>(tempPlacements);
                        } else {
                            maxPlacement.clear();
                            maxPlacement.addAll(tempPlacements);
                        }
                    }
                }  // childNode != null
            }

            if (maxPlacement != null && maxPlacement.size() > 0) {
                placements.clear();
                placements.addAll(maxPlacement);
            }

            return maxScore;
        }

        /**
         * Determines whether the word created perpendicular to the given direction by placing the tile
         * at the x,y coordinates is valid.
         *
         * @param board		The board where the existing tile have been placed on
         * @param startX	The x coordinate where the tile is being placed
         * @param startY	The y coordinate where the tile is being placed
         * @param toPlace	The tile that is being placed
         * @param direction	The direction perpendicular to the direction to check
         *
         * @return		<code>true</code> if the perpendicular word is valid, otherwise </code>false</code.
         */
       protected
        boolean validateCrossWordExists(final Board board, final int startX, final int startY, final Tile toPlace,
                                        final Direction direction)
        {
            boolean exists = false;

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

       protected
        Trie getTrie()
        {
            return this.trie;
        }

       protected
        void setTrie(final Trie trie)
        {
            this.trie = trie;
        }
    };
}
