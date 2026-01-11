.PHONY: client server compile clean game_test

compile: client server game_test

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



game_test: test_game.o main.o
	@gcc -o game_test test_game.o main.o

test_game.o: test_game.c main.h
	@gcc -c -Wall test_game.c

main.o: main.c main.h
	@gcc -c -Wall main.c
