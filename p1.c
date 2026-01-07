#include "main.h"

int main(){
  player1Logic();
  return 0;
}

void player1Logic(){
  printf("Connecting to Player 2\n");
  //TCP Handshake
//  printBoard(); //to be created
  int col=0;
  printf("Your token is X\n")
  printf("Which column do you want to put a piece in?\n");
  fgets(col,sizeof(col),stdin);
  return;
}
