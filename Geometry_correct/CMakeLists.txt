cmake_minimum_required(VERSION 3.20)
project(geometry)

add_subdirectory(src)
add_executable(main 1main.cpp)
target_include_directories(main PRIVATE /home/kostya/Repositories/C_plus_plus/Geometry_correct/src)
target_link_libraries(main PUBLIC geometry)
