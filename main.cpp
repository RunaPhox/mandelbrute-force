#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <string>

const int WIDTH{1000};
const int HEIGHT{1000};

bool init(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture,
          std::string windowTitle, int windowWidth, int windowHeight);
void close(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture);

void mandelbrute(uint8_t *rgbaPixelBuffer, int windowWidth, int windowHeight);
double map(double value, double high1, double low1, double low2, double high2);


bool
init(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture, std::string windowTitle, int windowWidth, int windowHeight)
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

	*texture = SDL_CreateTexture(
		*renderer,
		SDL_PIXELFORMAT_ABGR8888,
		SDL_TEXTUREACCESS_STATIC,
		windowWidth, windowHeight
	);

	if (!*texture) {
		std::cout << "could not create texture. SDL Error: "
		          << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void
close(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture)
{
	// destroy each object only if it was successfully created
	if (*texture) SDL_DestroyTexture(*texture);
	if (*renderer) SDL_DestroyRenderer(*renderer);
	if (*window) SDL_DestroyWindow(*window);

	SDL_Quit();
}

void
mandelbrute(uint8_t *rgbaPixelBuffer, int windowWidth, int windowHeight)
{
	double bright{};
	int pix{};

	int n{};

	const int maxIt{100};

	double a, b, ca, cb;
	const double range{1.4};

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

			pix = (x + y*windowWidth) * 4;

			rgbaPixelBuffer[pix]     = bright;
			rgbaPixelBuffer[pix + 1] = bright;
			rgbaPixelBuffer[pix + 2] = bright;
			rgbaPixelBuffer[pix + 3] = 0xff;
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
	SDL_Texture*  texture;

	if (!init(&window, &renderer, &texture, "Mandelbrute Force", WIDTH, HEIGHT)) {
		close(&window, &renderer, &texture);

		return 1;
	}

	bool quit{};
	SDL_Event evnt;

	uint8_t pixelBuffer[WIDTH*HEIGHT*4];

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

		mandelbrute(pixelBuffer, WIDTH, HEIGHT);

		SDL_UpdateTexture(texture, NULL, pixelBuffer, WIDTH*sizeof(*pixelBuffer));
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	close(&window, &renderer, &texture);

	return 0;
}
