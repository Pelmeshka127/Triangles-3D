FLAGS = -std=c++17 -O0

OPT_FLAGS = -DNDEBUG -std=c++17 -O2

# alltask: triangles

triangles: main.o point.o plane.o line.o vector.o triangle.o intersection.o
	g++ obj/main.o obj/intersection.o obj/point.o obj/plane.o obj/line.o obj/vector.o obj/triangle.o $(FLAGS) -o triangles

main.o: ./main.cpp
	g++ -c ./main.cpp $(FLAGS) -o obj/main.o

intersection.o: ./Intersection/intersection.cpp
	g++ -c ./Intersection/intersection.cpp $(FLAGS) -o obj/intersection.o

point.o: ./Geometry/point.cpp
	g++ -c ./Geometry/point.cpp $(FLAGS) -o obj/point.o

plane.o: ./Geometry/plane.cpp
	g++ -c ./Geometry/plane.cpp $(FLAGS) -o obj/plane.o

line.o: ./Geometry/line.cpp
	g++ -c ./Geometry/line.cpp $(FLAGS) -o obj/line.o

vector.o: ./Geometry/vector.cpp
	g++ -c ./Geometry/vector.cpp $(FLAGS) -o obj/vector.o

triangle.o: ./Geometry/triangle.cpp
	g++ -c ./Geometry/triangle.cpp $(FLAGS) -o obj/triangle.o