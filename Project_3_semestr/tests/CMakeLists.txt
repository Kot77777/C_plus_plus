add_subdirectory(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include)
include(GoogleTest)

file(GLOB_RECURSE TEST_SOURCES test_*.cpp)

foreach (TEST_FILE IN LISTS TEST_SOURCES)
	get_filename_component(TEST_FILE_NAME ${TEST_FILE} NAME_WE)
	set(EXECUTABLE_NAME run_${TEST_FILE_NAME})
	add_executable(${EXECUTABLE_NAME} ${TEST_FILE})
	target_link_libraries(${EXECUTABLE_NAME} gtest gtest_main ${PROJECT_NAME})
	gtest_discover_tests(${EXECUTABLE_NAME})
endforeach ()
