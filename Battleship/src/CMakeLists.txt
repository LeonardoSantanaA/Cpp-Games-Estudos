add_executable(${PROJECT_NAME} ./Battleship.cpp)
add_subdirectory(./includes/)
target_link_libraries(${PROJECT_NAME} PRIVATE utils)
