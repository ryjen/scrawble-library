
set(SOURCE_FILES
	game_logic.cpp
	board.cpp
	bag.cpp
	config.cpp
	player.cpp
	tile.cpp
	rack.cpp
	node.cpp
	arc.cpp
	path.cpp
	word.cpp
	gaddag.cpp
)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

set(HEADER_FILES
	game_logic.h
	algorith.h
	player.h
	tile.h
	config.h
	board.h
	bag.h
	rack.h
	node.h
	word.h
	path.h
	arc.h
	gaddag.h
)

install(FILES ${HEADER_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})

