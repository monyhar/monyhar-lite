monyhar-lite: main.o
	gcc main.o -o monyhar-lite

main.o: main.c
	gcc -c main.c -o main.o
