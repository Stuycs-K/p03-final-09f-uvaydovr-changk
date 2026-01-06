.PHONY: clean run compile

run: runme
	@./runme

clean:
	rm -f *.o runme

compile runme: main.o
	@gcc -Wall -o runme main.o

main.o: main.c
	@gcc -Wall -c main.c
