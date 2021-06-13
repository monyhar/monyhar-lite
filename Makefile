monyhar: main.o
	gcc main.o -o monyhar

main.o:
	gcc -c main.c -o main.o
