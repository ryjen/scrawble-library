
set(SOURCE_FILES
	scrawble.test.cpp
	graph.test.cpp
	main.test.cpp
)

add_executable(${TEST_PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${TEST_PROJECT_NAME} PUBLIC ${VENDOR_PATH}/bandit PUBLIC ${PROJECT_SOURCE_DIR}/src PUBLIC ${PROJECT_SOURCE_DIR}/src/vendor)

target_link_libraries (${TEST_PROJECT_NAME} ${PROJECT_NAME}_algo)

