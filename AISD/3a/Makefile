ifeq ($(METHOD),iter)	
	FLAG = -g -Wall -D ITERATOR
	FILE = liblab3_i.a
	COMPILER = -llab3_i
else
	FLAG = -g -Wall
	FILE = liblab3.a
	COMPILER = -llab3
endif
main.o : main.c
	gcc -c main.c -o main.o $(FLAG)

work_w_tab_i.o : work_w_tab_i.c
	gcc -c work_w_tab_i.c -o work_w_tab_i.o $(FLAG)

tools.o : tools.c
	gcc -c tools.c -o tools.o $(FLAG)

Files.o : Files.c
	gcc -c Files.c -o Files.o $(FLAG)

dialo.o : dialo.c
	gcc -c dialo.c -o dialo.o $(FLAG)

del_tab.o : del_tab.c
	gcc -c del_tab.c -o del_tab.o $(FLAG)

del_tab_i.o : del_tab_i.c
	gcc -c del_tab_i.c -o del_tab_i.o $(FLAG)

dialo_i.o : dialo_i.c
	gcc -c dialo_i.c -o dialo_i.o $(FLAG)

work_w_tab.o : work_w_tab.c
	gcc -c work_w_tab.c -o work_w_tab.o $(FLAG)

liblab3.a : del_tab.o Files.o tools.o work_w_tab.o dialo.o
	ar cr liblab3.a del_tab.o Files.o tools.o work_w_tab.o dialo.o

liblab3_i.a : del_tab_i.o Files.o tools.o work_w_tab_i.o dialo_i.o
	ar cr liblab3_i.a del_tab_i.o Files.o tools.o work_w_tab_i.o dialo_i.o

res : $(FILE) main.o
ifeq ($(METHOD),iter)
	rm -f del_tab.o  work_w_tab.o dialo.o liblab3.a res
else
	rm -f del_tab_i.o work_w_tab_i.o dialo_i.o liblab3_i.a res
endif
	gcc main.o -L. $(COMPILER) -o res $(FLAG)

clean:
	rm -f *.o *.a res
