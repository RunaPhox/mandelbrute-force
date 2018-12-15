#include <SDL2/SDL.h>
#include <iostream>

const int WIDTH{1280};
const int HEIGHT{720};

bool init(SDL_Window **window, std::string windowTitle, int windowWidth, int windowHeight);
void close(SDL_Window **window);


bool
init(SDL_Window **window, std::string windowTitle, int windowWidth, int windowHeight)
{
	SDL_Init(SDL_INIT_VIDEO);

	*window = SDL_CreateWindow(
		windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN
	);

	if (!*window) {
		std::cout << "could not create window. SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void
close(SDL_Window **window)
{
	SDL_DestroyWindow(*window);
	SDL_Quit();
}

int
main()
{
	SDL_Window* window;

	if (!init(&window, "title", WIDTH, HEIGHT)) {
		std::cout << "could not initialize SDL" << std::endl;
		return 1;
	}

	bool quit{};
	SDL_Event evnt;
	while (!quit) {
		while (SDL_PollEvent(&evnt)) {
			switch (evnt.type) {
				case SDL_QUIT:
					quit = true;
					break;
				default:
					break;
			}
		}
	}

	close(&window);

	return 0;
}
