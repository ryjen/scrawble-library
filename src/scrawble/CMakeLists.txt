
set(SOURCE_FILES
	game.cpp
	board.cpp
	bag.cpp
	lexicon/gaddag.cpp
	lexicon/node.cpp
	config.cpp
	player.cpp
	file_reader.cpp
)


add_library(${PROJECT_NAME} ${SOURCE_FILES})

set(HEADER_FILES
	game.h
	lexicon/gaddag.h
	lexicon/trie.h
	lexicon/loader.h
	lexicon/node.h
	file_reader.h
	player.h
	tile.h
	config.h
	board.h
	bag.h
)

INSTALL(FILES ${HEADER_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})

