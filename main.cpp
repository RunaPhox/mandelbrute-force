#include <SDL2/SDL.h>

#include <iostream>

const int WIDTH{1280};
const int HEIGHT{720};

bool init(SDL_Window **window, std::string windowTitle, int windowWidth, int windowHeight);
void close(SDL_Window **window);

void mandelbrute();
double map(double value, int high1, int low1, int low2, int high2);


bool
init(SDL_Window **window, std::string windowTitle, int windowWidth, int windowHeight)
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

	return true;
}

void
close(SDL_Window **window)
{
	// destroy each object only if it was successfully created
	if (*window) SDL_DestroyWindow(*window);

	SDL_Quit();
}

void
mandelbrute(int windowWidth, int windowHeight)
{
	double bright{};

	double imagPart{};
	double origImagPart{};

	double realPart{};
	double origRealPart{};

	double realSqrt{};
	double imagSqrt{};

	for (int y{}; y < windowHeight; ++y) {
		imagPart = map(y,0,HEIGHT, -2, 2); // map function here for y values
		origImagPart = imagPart;

		for (int x{}; x < windowWidth; ++x) {
			realPart = map(x, 0, windowWidth, -2, 2); // map function here for x values
			origRealPart = realPart;

			// calculate divergence
			for (int num{}; num < 100; ++num) {
				realSqrt = realPart*realPart - imagPart*imagPart;
				imagSqrt = 2 * realPart * imagPart;

				realPart = realSqrt + origRealPart;
				imagPart = imagSqrt + origImagPart;

				if (abs(realSqrt+imagSqrt) > 16) break;
			}
			
			if (num == 100) {
				bright = 0;
			} else {
				bright = map(num, 0, 100, 0, 1); // map function here for brigth values
				bright = map(sqrt(bright), 0, 1, 0, 255);
			}
			
			/*Put Pixels code here*/

		}
	}
}

double
map(double value, int high1, int low1, int low2, int high2)
{
	return low2 + (value - low1) * (high2 - low2) / (high1 - low1);
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
