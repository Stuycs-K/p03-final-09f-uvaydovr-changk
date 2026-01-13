#include "game.h"

//checks board to see if game is over
//returns which token wins
char checkBoard(char board[]){
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++ ) {
      char ch = board[r * COLS + c];

      if (c + 3 < COLS) { // check horizontally
        if (board[r * COLS + (c + 1)] == ch &&
            board[r * COLS + (c + 2)] == ch &&
            board[r * COLS + (c + 3)] == ch) {
          return ch;
        }
      }

      if (r + 3 < ROWS) { // check vertically
        if (board[(r+1) * COLS + c] == ch &&
            board[(r+2) * COLS + c] == ch &&
            board[(r+3) * COLS + c] == ch) {
          return ch;
        }
      }

      if (r + 3 < ROWS && c + 3 < COLS) {
        if (board[(r + 1) * COLS + (c + 1)] == ch &&
            board[(r + 2) * COLS + (c + 2)] == ch &&
            board[(r + 3) * COLS + (c + 3)] == ch) {
          return ch;
        }
      }

      if (r - 3 >= 0 && c + 3 < COLS) {
        if (board[(r - 1) * COLS + (c + 1)] == ch &&
            board[(r - 2) * COLS + (c + 2)] == ch &&
            board[(r - 3) * COLS + (c + 3)] == ch) {
          return ch;
        }
      }

    }
  }

  for (int i = 0; i < BOARD_SIZE; i++) {
    if (board[i] == '_' || board[i] == 0) {
      return 0;
    }
  }

  return 'D';
}

void printBoard(char * board){
  //prints board in specific format like this:
  //  _1_|_4_|_7_
  //  _2_|_5_|_8_
  //  _3_|_6_|_9_
  // *Actual board has more rows and columns
  // *numbering may change

  printf("\n ");
  for (int c = 0; c < COLS; c++) {
    printf("%d ", c);
  }
  printf("\n");
  for(int r = 0; r < ROWS; r++) {
    printf("|");
    for (int c = 0; c < COLS; c++) {
      int i = r * COLS + c;
      char ch = board[i];
      if(ch ==0) ch = '_';
      printf("%c|", ch);
    }
    printf("\n");
  }
  printf("\n");
}

int updateBoard(char * board,int col, char token){
  //updates board array
  //returns 0 if board updated
  //returns -1 if col was already filled

  if (col < 0 || col >= COLS) {
    return -1;
  }
  for (int r = ROWS - 1; r >= 0; r--) {
    int i = r * COLS + col;
    if (board[i] == '_' || board[i] == 0) {
      board[i] = token;
      return 0;
    }
  }
  return -1;
}

/* Things to do:
- Sighandler to stop a player program if the other player quits, and to stop both players if server quits (and print messages accordingly) (Currently not working as intended)
- Select to make sure players can't input moves when it's not their tournament
- Fix error where if player 2 is run before player 1, the server doesn't break *** (server.c)
- Server keeping track of all games in tournament
*/
