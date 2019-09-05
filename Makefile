all : main
.PHONY : all

clean :
		rm -f *.o main

main : main.o interface.o 
		gcc $^ -o $@

main.o : main.c interface.h 
interface.o : interface.c interface.h

%.o : %.c 
	gcc -c $<
