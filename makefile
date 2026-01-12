.PHONY: player server compile clean

compile: player server

player: player.o main.o networking.o
	@gcc -o player player.o main.o networking.o

player.o: player.c networking.h main.h
	@gcc -c -Wall player.c

server: server.o networking.o
	@gcc -o server server.o networking.o

server.o: server.c networking.h
	@gcc -c -Wall server.c

main.o: main.c main.h
	@gcc -c -Wall main.c

networking.o: networking.c networking.h
	@gcc -c -Wall networking.c

clean:
	rm -f *.o *~
	rm -f player server
