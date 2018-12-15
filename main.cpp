#include <SDL2/SDL.h>

#include <iostream>

const int WIDTH{1280};
const int HEIGHT{720};

bool init(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture,
          std::string windowTitle, int windowWidth, int windowHeight);
void close(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture);

void mandelbrute(int *rgbaPixelBuffer, int windowWidth, int windowHeight);
double map(double value, int high1, int low1, int low2, int high2);


bool
init(SDL_Window **window, SDL_Renderer **renderer, SDL_Texture **texture,
     std::string windowTitle, int windowWidth, int windowHeight)
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
		SDL_PIXELFORMAT_ARGB8888,
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
mandelbrute(int *rgbaPixelBuffer, int windowWidth, int windowHeight)
{
	double bright{};

	double imagPart{};
	double origImagPart{};

	double realPart{};
	double origRealPart{};

	double realSqrt{};
	double imagSqrt{};

	for (int y{}; y < windowHeight; ++y) {

		imagPart = map(y, 0, windowHeight , -2, 2); // map function here for y values
		origImagPart = imagPart;

		for (int x{}; x < windowWidth; ++x) {
			realPart = map(x, 0, windowWidth, -2, 2); // map function here for x values
			origRealPart = realPart;

			int num{};

			// calculate divergence
			for (num = 0; num < 100; ++num) {
				realSqrt = realPart*realPart - imagPart*imagPart;
				imagSqrt = 2 * realPart * imagPart;

				realPart = realSqrt + origRealPart;
				imagPart = imagSqrt + origImagPart;
			}
			
			if (num == 100) {
				bright = 0;
			} else {
				bright = map(num, 0, 100, 0, 1); // map function here for brigth values
				bright = map(sqrt(bright), 0, 1, 0, 255);
			}

			int pix{(x + y*windowWidth) * 4};

			rgbaPixelBuffer[pix]     = bright;
			rgbaPixelBuffer[pix + 1] = bright;
			rgbaPixelBuffer[pix + 2] = bright;
			std::cout << "asign to pixels done" << std::endl;
		}
	}
	std::cout << "done" << std::endl;
}

double
map(double value, int high1, int low1, int low2, int high2)
{
	return low2 + (value - low1) * (high2 - low2) / (high1 - low1);
}

int
main()
{
	SDL_Window*   window;
	SDL_Renderer* renderer;
	SDL_Texture*  texture;

	if (!init(&window, &renderer, &texture, "Mandelbrute Force", WIDTH, HEIGHT)) {
		std::cout << "could not initialize SDL" << std::endl;
		close(&window, &renderer, &texture);

		return 1;
	}

	bool quit{};
	SDL_Event evnt;

	int pixelBuffer[WIDTH*HEIGHT*4];

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
		SDL_UpdateTexture(texture, NULL, pixelBuffer, WIDTH*sizeof(int));
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	close(&window, &renderer, &texture);

	return 0;
}
