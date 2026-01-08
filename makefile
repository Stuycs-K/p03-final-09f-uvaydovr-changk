.PHONY: clean run compile

compile: main.o p1.o p2.o main.h
	@gcc -Wall -o p1 p1.o main.o
	@gcc -Wall -o p2 p2.o main.o

p1: p1.o
	@./p1

p2: p2.o
	@./p2

main.o: main.c main.h
	@gcc -Wall -c main.c

p1.o: p1.c main.h
	@gcc -Wall -c p1.c

p2.o: p2.c main.h
	@gcc -Wall -c p2.c

clean:
	rm -f *.o p1 p2
