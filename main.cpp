#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <string>

const int WIDTH{1000};
const int HEIGHT{1000};

bool init(SDL_Window **window, SDL_Renderer **renderer,
          std::string windowTitle, int windowWidth, int windowHeight);
void close(SDL_Window **window, SDL_Renderer **renderer);

void mandelbrute(SDL_Renderer **renderer, int windowWidth, int windowHeight, double range);
double map(double value, double high1, double low1, double low2, double high2);


bool
init(SDL_Window **window, SDL_Renderer **renderer, std::string windowTitle, int windowWidth, int windowHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		std::cout << "SDL initialization failed! SDL Error: "
		          << SDL_GetError() << std::endl;
		return false;
	}

	*window = SDL_CreateWindow(
		windowTitle.c_str(),                              // window title
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, // window x and y position
		windowWidth, windowHeight,                        // window width and height
		SDL_WINDOW_SHOWN                                  // window flags
	);

	if (!*window) {
		std::cout << "could not create window. SDL Error: "
		          << SDL_GetError() << std::endl;
		return false;
	}

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	if (!*renderer) {
		std::cout << "could not create renderer. SDL Error: "
		          << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void
close(SDL_Window **window, SDL_Renderer **renderer)
{
	// destroy each object only if it was successfully created
	if (*renderer) SDL_DestroyRenderer(*renderer);
	if (*window) SDL_DestroyWindow(*window);

	SDL_Quit();
}

void
mandelbrute(SDL_Renderer **renderer, int windowWidth, int windowHeight, double range)
{
	double bright{};

	int n{};

	const int maxIt{200};

	double a, b, ca, cb;

	for (int y{}; y < windowHeight; ++y) {
		for (int x{}; x < windowWidth; ++x) {
			a = map(x, 0, windowWidth, -range, range); // map function here for x values
			b = map(y, 0, windowHeight, -range, range); // map function here for y values

			ca = a;
			cb = b;

			// calculate divergence
			for (n = 0; n < maxIt; ++n) {
				double aa{a*a - b*b};
				double bb{2 * a * b};

				a = aa + ca;
				b = bb + cb;

				if (abs(a+b) > 16) break;
			}


			bright = 0;

			if (n != maxIt) {
				bright = map(
					sqrt(map(n, 0, maxIt, 0, 1)),
					0, 1, 0, 255
				);
			}

			SDL_SetRenderDrawColor(*renderer, bright*1.5, bright*2, bright/3, 0xff);
			SDL_RenderDrawPoint(*renderer, x, y);
		}
	}
}

double
map(double n, double start1, double stop1, double start2, double stop2)
{
	return (n - start1)/(stop1 - start1)*(stop2 - start2) + start2;
}

int
main()
{
	SDL_Window*   window;
	SDL_Renderer* renderer;

	if (!init(&window, &renderer, "Mandelbrute Force", WIDTH, HEIGHT)) {
		close(&window, &renderer);

		return 1;
	}

	bool quit{};
	bool changed{true};
	SDL_Event evnt;

	double range{2};

	while (!quit) {
		if (changed) {
			mandelbrute(&renderer, WIDTH, HEIGHT, range);
			SDL_RenderPresent(renderer);
			changed = false;
		}

		SDL_WaitEvent(&evnt);
		switch (evnt.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (evnt.key.keysym.sym) {
					case SDLK_KP_PLUS:
						range -= 0.1;
						changed = true;
						break;
					case SDLK_KP_MINUS:
						range += 0.1;
						changed = true;
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}

	close(&window, &renderer);

	return 0;
}
