FLAG = -g -Wall
res : tools.o matrix.o main.o
	gcc tools.o matrix.o main.o -o res $(FLAG)

tools.o : tools.c
	gcc -c tools.c -o tools.o $(FLAG)

matrix.o : matrix.c
	gcc -c matrix.c -o matrix.o $(FLAG)

main.o : main.c
	gcc -c main.c -o main.o $(FLAG)
