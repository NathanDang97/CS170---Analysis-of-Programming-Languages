#To run, put this file together with lexer.h, and lexer.c
#in the same directory. Run "make". Then the executable
#is "schemer," which just takes a line of input and
#breaks it up into tokens.

schemer: main.o parser.o lexer.o evaluator.o
	gcc -o scheme main.o parser.o lexer.o evaluator.o

main.o: main.c
	gcc -c main.c

evaluator.o: evaluator.c
	gcc -c evaluator.c

parser.o: parser.c
	gcc -c parser.c

lexer.o: lexer.c
	gcc -c lexer.c

clean:
	rm -f *~ *.o *.a

#^^^^^^This space must be a TAB!!.
