all : main 
.PHONY : all 

clean :
		rm -f *.o main 

main : main.o interface.o submit.o 
		gcc main.o interface.o submit.o -o main 

main.o : main.c interface.h submit.h 
		gcc -c main.c 

interface.o : interface.c interface.h 
		gcc -c interface.c 

submit.o : submit.c submit.h 
		gcc -c submit.c 

