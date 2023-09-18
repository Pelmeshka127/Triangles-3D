FLAGS = -std=c++17 -O0

OPT_FLAGS = -DNDEBUG -std=c++17 -O2

alltask: triangles

triangles: main.o
	g++ obj/main.o $(FLAGS) -o ./obj/main

main.o: ./main.cpp
	g++ -c ./main.cpp $(FLAGS) -o obj/main.o