monyhar-lite: main.o
	g++ main.o -o monyhar-lite

main.o: main.cpp
	g++ -c main.cpp -o main.o
