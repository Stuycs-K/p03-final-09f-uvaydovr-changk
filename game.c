#include "game.h"

//checks board to see if game is over
//returns which token wins
//returns D if it's a draw
char checkBoard(char board[]){
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++ ) {
      char ch = board[r * COLS + c];

      char token;

      if (ch == 'X') {
        token = 'X';
      } else if (ch == 'O') {
        token = 'O';
      } else {
        continue;
      }

      if (c + 3 < COLS) { // check horizontally
        if (board[r * COLS + (c + 1)] == ch &&
            board[r * COLS + (c + 2)] == ch &&
            board[r * COLS + (c + 3)] == ch) {
          return token;
        }
      }

      if (r + 3 < ROWS) { // check vertically
        if (board[(r+1) * COLS + c] == ch &&
            board[(r+2) * COLS + c] == ch &&
            board[(r+3) * COLS + c] == ch) {
          return token;
        }
      }

      if (r + 3 < ROWS && c + 3 < COLS) { //diagonally
        if (board[(r + 1) * COLS + (c + 1)] == ch &&
            board[(r + 2) * COLS + (c + 2)] == ch &&
            board[(r + 3) * COLS + (c + 3)] == ch) {
          return token;
        }
      }

      if (r - 3 >= 0 && c + 3 < COLS) { //diagonally
        if (board[(r - 1) * COLS + (c + 1)] == ch &&
            board[(r - 2) * COLS + (c + 2)] == ch &&
            board[(r - 3) * COLS + (c + 3)] == ch) {
          return token;
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


//prints board in specific column format
void printBoard(char * board){
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


//updates board array
//returns 0 if board updated
//returns -1 if col was already filled
int updateBoard(char * board,int col, char token){
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
- Select to make sure players can't input moves when it's not their tournament
- Server keeping track of all games in tournament
*/
