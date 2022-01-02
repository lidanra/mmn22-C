myset: myset.o input.o set.o
	gcc -g -ansi myset.o input.o set.o -o myset

myset.o: myset.c input.h
	gcc -c -Wall -ansi -pedantic myset.c -o myset.o

manage_input.o: input.c set.o input.h 
	gcc -c -Wall -ansi -pedantic input.c -o input.o

set.o: set.c set.h
	gcc -c -Wall -ansi -pedantic set.c -o set.o 
