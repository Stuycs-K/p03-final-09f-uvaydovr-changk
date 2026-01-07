.PHONY: clean run compile

run: runme
	@./runme

p1: p1.o
	@./p1

p2: p2.o
	@./p2

compile runme: main.o p1.o p2.o main.h
	@gcc -Wall -o runme main.o
	@gcc -Wall -o p1 p1.o
	@gcc -Wall -o p2 p2.o

main.o: main.c main.h
	@gcc -Wall -c main.c

p1.o: p1.c main.h
	@gcc -Wall -c p1.c

p2.o: p2.c main.h
	@gcc -Wall -c p2.c

clean:
	rm -f *.o runme p1 p2
