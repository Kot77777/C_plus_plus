Geom: main.o Geometry.o
	g++ main.o Geometry.o -o Geom

main.o: main.cpp Geometry.hpp
	g++ main.cpp -c -o main.o

Geometry.o: Geometry.cpp Geometry.hpp
	g++ Geometry.cpp -c -o Geometry.o

