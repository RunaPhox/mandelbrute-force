#include <SDL2/SDL.h>

const int WIDTH{1280};
const int HEIGHT{720};

SDL_Window *window;

int
main(int argc, char *argv[])
{
	//SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("title", WIDTH, HEIGHT, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOW_SHOWN);

	// 3000 milliseconds
	SDL_Sleep(3000);

	SDL_Quit();
	return 0;
}
