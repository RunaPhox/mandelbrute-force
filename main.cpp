#include <SDL2/SDL.h>
#include <iostream>

const int WIDTH{1280};
const int HEIGHT{720};

SDL_Window *window;

int
main()
{
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("title", WIDTH, HEIGHT, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cout << "could not create window. SDL Error: " << SDL_GetError() << std::endl;
	}

	// 3000 milliseconds
	SDL_Delay(3000);

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
