#include <iostream>
#include <SDL.h>

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	std::cout << "Setup SDL2 with CMake" << std::endl;
	system("pause");
	SDL_Quit();
	return 0;
}