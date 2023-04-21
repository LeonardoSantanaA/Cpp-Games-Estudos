cmake_minimum_required(VERSION 3.17)
project(TextInvaders)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(TextInvaders ./TextInvaders.cpp ./CursesUtils.cpp)

target_link_libraries(TextInvaders ${CURSES_LIBRARIES})
