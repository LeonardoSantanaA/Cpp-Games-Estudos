cmake_minimum_required(VERSION 3.8)

project(SDL2Test)


find_package(SDL2 REQUIRED) 


add_executable(SDL2Setup "Setup.cpp" 
"src/Graphics/Color.cpp" 
"src/Graphics/ScreenBuffer.cpp" 
"src/Graphics/Screen.cpp"
"src/Utils/Utils.cpp"
"src/Utils/Vec2D.cpp"
"src/Utils/Vec2D.h"
"src/Shapes/Line2D.cpp"
 "src/Shapes/Shape.h" "src/Shapes/Shape.cpp" 
 "src/Shapes/Triangle.h" "src/Shapes/Triangle.cpp" 
 "src/Shapes/AARectangle.h" "src/Shapes/AARectangle.cpp" 
 "src/Shapes/Circle.h" "src/Shapes/Circle.cpp")

target_link_libraries(SDL2Setup SDL2::SDL2 SDL2::SDL2main)
