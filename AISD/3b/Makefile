FLAG = -g -Wall -lm
main.o : main.c
	gcc -c main.c -o main.o $(FLAG)

work_w_tab.o : work_w_tab.c
	gcc -c work_w_tab.c -o work_w_tab.o $(FLAG)

tools.o : tools.c
	gcc -c tools.c -o tools.o $(FLAG)

Files.o : Files.c
	gcc -c Files.c -o Files.o $(FLAG)

dialo.o : dialo.c
	gcc -c dialo.c -o dialo.o $(FLAG)

del_tab.o : del_tab.c
	gcc -c del_tab.c -o del_tab.o $(FLAG)

liblab3.a : del_tab.o Files.o tools.o work_w_tab.o dialo.o
	ar cr liblab3.a del_tab.o Files.o tools.o work_w_tab.o dialo.o

res : liblab3.a main.o
	gcc main.o -L. -llab3 -o res $(FLAG)

clean:
	rm -f *.o *.a res
