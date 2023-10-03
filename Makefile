alltask: triangles

FLAGS 	  	= -std=c++17 -O0 

OPT_FLAGS 	= -DNDEBUG -std=c++17 -O2

triangles: main intersect point plane line vector triangle double_numbers
	g++ obj/main.o obj/intersect.o obj/point.o obj/plane.o obj/line.o obj/vector.o obj/triangle.o obj/double_numbers.o $(OPT_FLAGS) -o triangles

# triangles: intersect
# 	g++ obj/intersection.o $(FLAGS) -o triangles

# main.o: ./main.cpp ./Intersection/intersection.cpp ./Geometry/point.cpp ./Geometry/plane.cpp ./Geometry/line.cpp ./Geometry/vector.cpp ./Geometry/triangle.cpp ./MathLibs/double_numbers.cpp
# 	g++ -c ./main.cpp ./Intersection/intersection.cpp ./Geometry/point.cpp ./Geometry/plane.cpp ./Geometry/line.cpp ./Geometry/vector.cpp ./Geometry/triangle.cpp ./MathLibs/double_numbers.cpp $(FLAGS) -o ./obj/main.o

main:
	g++ -c ./main.cpp $(OPT_FLAGS) -o obj/main.o

intersect:
	g++ -c ./Intersection/intersection.cpp $(OPT_FLAGS) -o obj/intersect.o

point:
	g++ -c ./Geometry/point.cpp $(OPT_FLAGS) -o obj/point.o

plane:
	g++ -c ./Geometry/plane.cpp $(OPT_FLAGS) -o obj/plane.o

line:
	g++ -c ./Geometry/line.cpp $(OPT_FLAGS) -o obj/line.o

vector:
	g++ -c ./Geometry/vector.cpp $(OPT_FLAGS) -o obj/vector.o

triangle:
	g++ -c ./Geometry/triangle.cpp $(OPT_FLAGS) -o obj/triangle.o

double_numbers:
	g++ -c ./MathLibs/double_numbers.cpp $(OPT_FLAGS) -o obj/double_numbers.o