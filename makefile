.PHONY: client server compile clean player

compile: player.o server.o networking.o main.o
	@gcc -o player player.o networking.o main.o
	@gcc -o server server.o networking.o

player:
	@./player $(ARGS)

server:
	@./server

player.o: player.c networking.h main.h
	@gcc -c -Wall player.c

server.o: server.c networking.h
	@gcc -c -Wall server.c

networking.o: networking.c networking.h
	@gcc -c -Wall networking.c

main.o: main.c main.h
	@gcc -c -Wall main.c

clean:
	rm -f *.o *~
	rm -f player server
