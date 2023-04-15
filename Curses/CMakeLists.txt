cmake_minimum_required(VERSION 3.17)
project(curses)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(curses ./Curses.cpp)
target_link_libraries(curses ${CURSES_LIBRARIES})
