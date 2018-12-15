all: main.cpp
	g++ main.cpp -lSDL2 -Wall -Wextra -Werror -pedantic -std=c++17 -ggdb3
clear:
	rm *.o *.out
