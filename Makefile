alltask: triangles

FLAGS 	  	= -std=c++17 -O0 

OPT_FLAGS 	= -DNDEBUG -std=c++17 -O2

triangles: main point plane line vector triangle intersection double_numbers
	g++ obj/main.o obj/point.o obj/plane.o obj/line.o obj/vector.o obj/triangle.o obj/intersection.o obj/double_numbers.o $(FLAGS) -o triangles

# main.o: ./main.cpp ./Intersection/intersection.cpp ./Geometry/point.cpp ./Geometry/plane.cpp ./Geometry/line.cpp ./Geometry/vector.cpp ./Geometry/triangle.cpp ./MathLibs/double_numbers.cpp
# 	g++ -c ./main.cpp ./Intersection/intersection.cpp ./Geometry/point.cpp ./Geometry/plane.cpp ./Geometry/line.cpp ./Geometry/vector.cpp ./Geometry/triangle.cpp ./MathLibs/double_numbers.cpp $(FLAGS) -o ./obj/main.o

main:
	g++ -c ./main.cpp $(FLAGS) -o obj/main.o

intersection:
	g++ -c ./Intersection/intersection.cpp $(FLAGS) -o obj/intersection.o

point:
	g++ -c ./Geometry/point.cpp $(FLAGS) -o obj/point.o

plane:
	g++ -c ./Geometry/plane.cpp $(FLAGS) -o obj/plane.o

line:
	g++ -c ./Geometry/line.cpp $(FLAGS) -o obj/line.o

vector:
	g++ -c ./Geometry/vector.cpp $(FLAGS) -o obj/vector.o

triangle:
	g++ -c ./Geometry/triangle.cpp $(FLAGS) -o obj/triangle.o

double_numbers:
	g++ -c ./MathLibs/double_numbers.cpp $(FLAGS) -o obj/double_numbers.o