FLAGS = -std=c++17 -O0

OPT_FLAGS = -DNDEBUG -std=c++17 -O2

alltask: triangles

triangles: point.o main.o
	g++ obj/point.o obj/main.o $(FLAGS) -o ./obj/main

point.o: ./Point/point.cpp
	g++ -c ./Point/point.cpp $(FLAGS) -o obj/point.o

main.o: ./main.cpp
	g++ -c ./main.cpp $(FLAGS) -o obj/main.o