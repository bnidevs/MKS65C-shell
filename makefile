all: shell.o
	gcc shell.o

clean:
	rm -f *~ *.gch* a.out *.o *#*

run:
	./a.out

shell.o: shell.c
	gcc -c shell.c