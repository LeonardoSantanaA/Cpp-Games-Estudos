cmake_minimum_required(VERSION 3.17)
project(curses)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(curses ./Curses.cpp)
add_executable(cursesExample ./CursesExample.cpp)

target_link_libraries(curses ${CURSES_LIBRARIES})
target_link_libraries(cursesExample ${CURSES_LIBRARIES})
