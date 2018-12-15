all: main.cpp
	g++ main.cpp -lSDL2 -Wall -Wextra -Werror -pedantic -std=c++17 -ggdb3

andrun: all
	./a.out

clear:
	rm *.o *.out
