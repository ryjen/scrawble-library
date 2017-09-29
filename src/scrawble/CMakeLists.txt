
set(SOURCE_FILES
	game_logic.cpp
	board.cpp
	bag.cpp
	config.cpp
	player.cpp
	tile.cpp
	rack.cpp
	core/gaddag.cpp
	core/node.cpp
)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

set(HEADER_FILES
	game_logic.h
	player.h
	tile.h
	config.h
	board.h
	bag.h
	rack.h
)

install(FILES ${HEADER_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})

