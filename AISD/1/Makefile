res : main.o matrix.o tools.o
	gcc main.o matrix.o tools.o -o res -g -Wall

main.o : main.c
	gcc -c main.c -o main.o -g -Wall

matrix.o : matrix.c
	gcc -c matrix.c -o matrix.o -g -Wall

tools.o : tools.c
	gcc -c tools.c -o tools.o -g -Wall

clean : 
	rm res *.o
