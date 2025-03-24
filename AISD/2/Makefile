FLAG = -g -Wall -lm
FLAG_V = -g -Wall -lm -D VECTOR
FLAG_L = -g -Wall -lm -D LIST
ifeq ($(LIB),stat)
	ifeq ($(QUEUE),V)
		FILES = main_V.o libvector.a
	else
		FILES = main_L.o liblist.a
	endif
else
	ifeq ($(QUEUE),V)
		FILES = main_V.o libvector.so
	else
		FILES = main_L.o liblist.so
	endif
endif

main_L.o : main.c
	gcc -c main.c -o main_L.o $(FLAG_L)

main_V.o : main.c
	gcc -c main.c -o main_V.o $(FLAG_V)

vector.o : vector.c
	gcc -c -fPIC vector.c -o vector.o $(FLAG)

list.o : list.c
	gcc -c -fPIC list.c -o list.o $(FLAG)
	
liblist.a : list.o
	ar cr liblist.a list.o

libvector.a : vector.o
	ar cr libvector.a vector.o

liblist.so : list.o
	gcc -shared -o liblist.so list.o

libvector.so : vector.o
	gcc -shared -o libvector.so vector.o
	
res: $(FILES) 
ifeq ($(LIB),stat)
	rm -f *.so res
ifeq ($(QUEUE),V)
	gcc main_V.o -L. -lvector -o res $(FLAG_V)
else
	gcc main_L.o -L. -llist -o res $(FLAG_L)
endif
else
	rm -f *.a res
ifeq ($(QUEUE),V)
	gcc main_V.o -L. -lvector -Wl,-rpath,. -o res $(FLAG_V)
else
	gcc main_L.o -L. -llist -Wl,-rpath,. -o res $(FLAG_L)
endif
endif
clean:
	rm -f *.o *.a *.so res

