.PHONY: client server compile clean

compile: client server

client: player.o networking.o
	@gcc -o player player.o networking.o

server: server.o networking.o
	@gcc -o server server.o networking.o

player.o: player.c networking.h
	@gcc -c -Wall player.c

server.o: server.c networking.h
	@gcc -c -Wall server.c

networking.o: networking.c networking.h
	@gcc -c -Wall networking.c

clean:
	rm -f *.o *~
	rm -f player server
