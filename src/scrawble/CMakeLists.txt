
set(LIBRARY_FILES
	scrawble.cpp
	board.cpp
	bag.cpp
	lexicon/gaddag.cpp
	lexicon/node.cpp
)


add_library(${PROJECT_NAME}_algo ${LIBRARY_FILES})

set(SOURCE_FILES 
	player.cpp
	config.cpp
	io.cpp
	main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_algo ${CURSES_LIBRARIES})

set(HEADER_FILES
	scrawble.h
	game.h
	lexicon/gaddag.h
	lexicon/trie.h
	lexicon/loader.h
	lexicon/node.h
)

INSTALL(FILES ${HEADER_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})

