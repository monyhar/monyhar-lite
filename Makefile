monyhar-lite: main.o
	gcc main.o -o monyhar-lite

main.o:
	gcc -c main.c -o main.o
