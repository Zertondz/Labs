FLAG = -g -Wall -lm -lcgraph -lgvc
main.o : main.c
	gcc -c main.c -o main.o $(FLAG)

tree.o : tree.c
	gcc -c tree.c -o tree.o $(FLAG)

tools.o : tools.c
	gcc -c tools.c -o tools.o $(FLAG)

dialog.o : dialog.c
	gcc -c dialog.c -o dialog.o $(FLAG)

calibrate.o : calibrate.c
	gcc -c calibrate.c -o calibrate.o $(FLAG)

add.o : add.c
	gcc -c add.c -o add.o $(FLAG)

liblab3.a :  tools.o tree.o dialog.o calibrate.o add.o
	ar cr liblab3.a  tools.o tree.o dialog.o calibrate.o add.o

res : liblab3.a main.o
	gcc main.o -L. -llab3 -o res $(FLAG)

clean:
	rm -f *.o *.a res
