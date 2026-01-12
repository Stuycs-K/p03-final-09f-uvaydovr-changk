.PHONY: client server compile clean

compile: client server

client: client.o player.o main.o networking.o
	@gcc -o client client.o player.o main.o networking.o

client.o: client.c networking.h main.h
	@gcc -c -Wall client.c

server: server.o networking.o
	@gcc -o server server.o networking.o

server.o: server.c networking.h
	@gcc -c -Wall server.c

player.o: player.c networking.h main.h
	@gcc -c -Wall player.c

main.o: main.c main.h
	@gcc -c -Wall main.c

networking.o: networking.c networking.h
	@gcc -c -Wall networking.c

clean:
	rm -f *.o *~
	rm -f client server
