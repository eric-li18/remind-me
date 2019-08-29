all : main
.PHONY : all

clean :
		rm -f *.o main

main : main.o interface.o submit.o
		gcc $^ -o $@

main.o : main.c interface.h submit.h
interface.o : interface.c interface.h
submit.o : submit.c submit.h

%.o : %.c 
	gcc -c $<