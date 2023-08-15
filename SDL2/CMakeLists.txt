cmake_minimum_required(VERSION 3.8)

project(SDL2Test)


find_package(SDL2 REQUIRED) 


add_executable(SDL2Setup "Setup.cpp")

target_link_libraries(SDL2Setup SDL2::SDL2 SDL2::SDL2main)
