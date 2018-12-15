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

double mapping(double value, int high1, int low1, int low2, int high2)
{
	return low2 + (value - low1) * (high2 - low2) / (high1 - low1);
}

void
mandelbrute()
{
    double brigth;
    for (int y = 0; y < HEIGHT; ++y)
    {
        double imagPart = mapping(y,0,HEIGHT,-2,2); //map function here for y values
        double origImagPart = imagPart;
        for (int x = 0; x < WIDTH; ++x)
        {
            double realPart = mapping(x,0,WIDTH,-2,2); //map function here for x values
            double origRealPart = realPart;

            //Calcule divergence
            for (int num = 0; num < 100; ++num)
            {
                realSqrt = realPart*realPart - imagPart*imagPart;
                imagSqrt = 2 * realPart * imagPart;

                realPart = realSqrt + origRealPart;
                imagPart = imagSqrt + origImagPart;

                if (abs(realSqrt+imagSqrt)>16) break;

                if (num == 100)
                    brigth = 0;
                else
                {
                    brigth = mapping(num, 0, 100, 0, 1); //map function here for brigth values
                    brigth = mapping(sqrt(brigth), 0, 1, 0, 255);
                }
            }
        }
    }
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
