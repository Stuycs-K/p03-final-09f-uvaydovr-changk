#include "main.h"

int checkBoard(char * board){
  //checks board to see if game is over
  //returns -1 if board full with no winner
  //returns 0 if game is not over
  //returns 1 if p1 wins and 2 if p2 wins
  return 0;
}

void printBoard(char * board){
  //prints board in specific format like this:
  //  _1_|_4_|_7_
  //  _2_|_5_|_8_
  //  _3_|_6_|_9_
  // *Actual board has more rows and columns
  // *numbering may change

  printf("\n 0 1 2 3 4 5 6\n");
  for(int r = 0; r < ROWS; r++) {
    printf("%d", r);
    for (int c = 0; c < COLS; c++) {
      int i = r * COLS + c;
      char ch = board[i];
      if(ch ==0) ch = '_';
      printf("%c ", ch);
    }
    printf("\n");
  }
  printf("\n");
}

/*

_1_|_2_|_3_|_4_|_5_|
___|___|___|___|___|
___|___|___|___|___|
___|___|___|___|___|

*/

int updateBoard(char * board,int col){
  //updates board array
  //returns 0 if board updated
  //returns -1 if col was already filled

  if (col < 0 || col > COLS) {
    return -1;
  }
  for (int r = ROWS - 1; r >= 0; r++) {
    int i =
    if (board[i] == '_' || board[i] == 0) {
      board[i] = 'X';
      return 0;
    }
  }
  return -1;
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

// user input >> 2
// take the number, looks at the array for that column
// starts from bottom row and strcmp to see if it's "_" >> then changes value to X/O
// if it's not, then it goes up the rows


/*
1. we need a server!
2. forks off a subserver and runs the game logic there
3. server knows who wins and loses (maybe enter player names at the start?)
4. two clients (can add more clients later) that are the players
5. sockets :(
6. networking lab

*/
