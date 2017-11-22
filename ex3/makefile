all: sudukusolver

sudukusolver: genericdfs.o sudukutree.o sudukusolver.o stack.o
	gcc -Wextra -Wall -Wvla -g genericdfs.o sudukutree.o sudukusolver.o stack.o -o sudukusolver -lm 

genericdfs.o: genericdfs.h genericdfs.c
	gcc -Wextra -Wall -Wvla -c genericdfs.c

sudukutree.o: sudukutree.c sudukutree.h
	gcc -Wextra -Wall -Wvla -c sudukutree.c

sudukusolver.o: sudukusolver.c genericdfs.h sudukutree.h stack.h
	gcc -Wextra -Wall -Wvla -c sudukusolver.c

stack.o : stack.c stack.h
	gcc -Wextra -Wall -Wvla -c stack.c

genericdfs.a: genericdfs.o
	ar rcs genericdfs.a genericdfs.o

clean:
	rm -f *.o *.a
