FLAG = -g -Wall -lm -lcgraph -lgvc
main.o : main.c
	gcc -c main.c -o main.o $(FLAG)

tools.o : tools.c
	gcc -c tools.c -o tools.o $(FLAG)

dialoc.o : dialoc.c
	gcc -c dialoc.c -o dialoc.o $(FLAG)

graph.o : graph.c
	gcc -c graph.c -o graph.o $(FLAG)

add.o : add.c
	gcc -c add.c -o add.o $(FLAG)

liblab3.a : tools.o dialoc.o graph.o add.o
	ar cr liblab3.a  tools.o dialoc.o graph.o add.o

res : liblab3.a main.o
	gcc main.o -L. -llab3 -o res $(FLAG)

clean:
	rm -f *.o *.a res
