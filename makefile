.PHONY: player server compile clean run

compile: player server

player: player.o networking.o game.o
	@gcc -o player player.o networking.o game.o

server: server.o networking.o
	@gcc -o server server.o networking.o

player.o: player.c networking.h game.h
	@gcc -c -Wall player.c

server.o: server.c networking.h
	@gcc -c -Wall server.c

game.o: game.c game.h
	@gcc -c -Wall game.c

networking.o: networking.c networking.h
	@gcc -c -Wall networking.c

clean:
	rm -f *.o *~
	rm -f player server game_test leaderboard.txt
