output: main.o 
	g++ main.o -o output
main.o: main.cpp maze.hpp maze.cpp
	g++ -c main.cpp maze.hpp maze.cpp

