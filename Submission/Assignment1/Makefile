
# This is the Makefile for main.c, Stack.c and Stack.h
# To use it, put it in the same directory as those three files.
# To compile, simply type "make" at the command line.
# To remove all object code, type "make clean" (this removes
# all ".o" and ".a" files)

# Executable file "exec" depends on main.o and IntQueue.o
exec: main.o Stack.o
	gcc -o exec main.o Stack.o

main.o: main.c
	gcc -c main.c

IntQueue.o: Stack.c
	gcc -c Stack.c

clean:
	rm -f *~ *.o *.a
#^^^This space must be a TAB!!.