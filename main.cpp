#include <SDL2/SDL.h>

const int WIDTH{1280};
const int HEIGHT{720};

SDL_Window *window;

int
main()
{
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	// 3000 milliseconds
	SDL_Delay(3000);

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
