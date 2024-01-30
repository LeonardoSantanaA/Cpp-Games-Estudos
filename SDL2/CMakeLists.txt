cmake_minimum_required(VERSION 3.8)

project(SDL2Test)

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

find_package(SDL2 REQUIRED) 
find_package(SDL2_mixer REQUIRED)

add_executable(ArcadeGame  #WIN32
"Setup.cpp" 
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
"src/Shapes/Circle.h" "src/Shapes/Circle.cpp" 
"src/App/App.h" "src/App/App.cpp" 
"src/Scenes/Scene.h" 
"src/Scenes/ArcadeScene.h" "src/Scenes/ArcadeScene.cpp" 
"src/Input/InputAction.h" 
"src/Input/GameController.h" "src/Input/GameController.cpp" 
"src/Input/InputController.h" "src/Input/InputController.cpp" 
"src/Games/Game.h" 
"src/Scenes/GameScene.h" "src/Scenes/GameScene.cpp" 
"src/Utils/FileCommandLoader.h" "src/Utils/FileCommandLoader.cpp" 
"src/Games/BreakOut/BreakOut.h" "src/Games/BreakOut/BreakOut.cpp" 
"src/Games/BreakOut/BoundaryEdge.h" 
"src/Games/BreakOut/Excluder.h" "src/Games/BreakOut/Excluder.cpp"
"src/Games/BreakOut/Paddle.h" "src/Games/BreakOut/Paddle.cpp"
"src/Games/BreakOut/Ball.h" "src/Games/BreakOut/Ball.cpp"
"src/Games/BreakOut/LevelBoundary.h" "src/Games/BreakOut/LevelBoundary.cpp"
"src/Games/BreakOut/Block.h" "src/Games/BreakOut/Block.cpp" 
"src/Games/BreakOut/BreakoutGameLevel.h" "src/Games/BreakOut/BreakoutGameLevel.cpp"
"src/Utils/ScoreFileLoader.h" "src/Utils/ScoreFileLoader.cpp"
"src/Games/Tetris/Tetris.h" "src/Games/Tetris/Tetris.cpp" 
"src/Games/Tetris/Playfield.h" "src/Games/Tetris/Playfield.cpp" 
"src/Games/Tetris/Tetromino.h" "src/Games/Tetris/Tetromino.cpp"
"src/Games/Tetris/Collider.h" "src/Games/Tetris/Collider.cpp"
"src/Games/Tetris/Blocks.h" "src/Games/Tetris/Blocks.cpp" 
"src/Games/Tetris/Ghost.h" "src/Games/Tetris/Ghost.cpp" 
"src/Graphics/BMPImage.h" "src/Graphics/BMPImage.cpp" 
"src/Graphics/SpriteSheet.h" "src/Graphics/SpriteSheet.cpp" 
"src/Graphics/BitmapFont.h" "src/Graphics/BitmapFont.cpp"   
"src/Utils/Sound.h" "src/Utils/Sound.cpp" "src/App/Button.h" 
"src/App/Button.cpp" "src/Scenes/ButtonOptionsScene.cpp" 
"src/Scenes/NotImplementedScene.h" "src/Scenes/NotImplementedScene.cpp" 
"src/Scenes/SelectNameScene.h" "src/Scenes/SelectNameScene.cpp"
"src/Scenes/ShowScoreScene.h" "src/Scenes/ShowScoreScene.cpp" 
"src/Graphics/Animation.h" "src/Graphics/Animation.cpp"
"src/Graphics/AnimationPlayer.h" "src/Graphics/AnimationPlayer.cpp"
"src/Graphics/AnimatedSprite.h" "src/Graphics/AnimatedSprite.cpp" 
"src/Games/Asteroids/Asteroids.h" "src/Games/Asteroids/Asteroids.cpp" 
"src/Games/Asteroids/Ship.h" "src/Games/Asteroids/Ship.cpp" 
"src/Games/Asteroids/Bullet.h" "src/Games/Asteroids/Bullet.cpp" "src/Games/Asteroids/Comet.h" "src/Games/Asteroids/Comet.cpp" "src/Games/Pacman/PacmanGame.h" "src/Games/Pacman/PacmanGame.cpp" "src/Scenes/Pacman/PacmanStartScene.cpp" "src/Scenes/Pacman/PacmanStartScene.h" "src/Games/Pacman/PacmanLevel.h" "src/Games/Pacman/PacmanLevel.cpp" "src/Games/Pacman/PacmanGameUtils.h" "src/Games/Pacman/PacmanGameUtils.cpp")

target_link_libraries(ArcadeGame SDL2::SDL2 SDL2::SDL2main SDL2_mixer::SDL2_mixer)