cmake_minimum_required(VERSION 3.20)
project(geometry)

add_subdirectory(src)

add_executable(MAIN 1main.cpp)
target_link_libraries(MAIN ${PROJECT_NAME})
