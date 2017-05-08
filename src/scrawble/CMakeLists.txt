
set(LIBRARY_FILES
	scrawble.cpp
)


add_library(${PROJECT_NAME}_algo ${LIBRARY_FILES})

set(SOURCE_FILES 
	main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_algo)

set(HEADER_FILES
	scrawble.h
	graph.h
	lexicon/gaddag.h
	lexicon/trie.h
	lexicon/loader.h
	lexicon/node.h
)

INSTALL(FILES ${HEADER_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})

