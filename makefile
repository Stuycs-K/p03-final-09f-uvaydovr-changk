.PHONY: player server compile clean game_test

compile: player.o server.o networking.o game.o test_game.o
	@gcc -o player player.o networking.o game.o
	@gcc -o server server.o networking.o

player:
	@./player $(ARGS)

player.o: player.c networking.h game.h
	@gcc -c -Wall player.c

server:
	@./server

server.o: server.c networking.h
	@gcc -c -Wall server.c

game.o: game.c game.h
	@gcc -c -Wall game.c

networking.o: networking.c networking.h
	@gcc -c -Wall networking.c

clean:
	rm -f *.o *~
	rm -f player server game_test

game_test: test_game.o game.o
	@gcc -o game_test test_game.o game.o

test_game.o: test_game.c game.h
	@gcc -c -Wall test_game.c
