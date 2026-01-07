#include "main.h"
int main(){
  return 0;
}

// P1 and P2 are both run targets
// Player 1 calls 'make P1' which uses player1Logic()
// Player 2 calls 'make P2' which uses player2Logic()
// P1 turn gets stored into file (name ex. board.txt)
// P2 turn, board gets printed by reading from file, P2 turn stored
// P1 same as P2 turn and so on
// Goes until game ends (check before each new turn if someone won or no space left on board)

// board.txt:
// store tokens in a file as numbered rows
// player inputs a column number (maybe mod by column number like 3)
// boxes are numbered
// prints out grid _file[0]_| repeatedly
// file probably created in main and filled with _

// Debugging:
// create a view function that prints boards

// Original Ideas:
// assign player 1 and 2 by PID?
// main function that forks into two different things
// semaphoresssss
