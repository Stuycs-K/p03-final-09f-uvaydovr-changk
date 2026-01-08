#include "main.h"

int main(){
  player2Logic();
  return 0;
}

 void player2Logic(){
  printf("Connecting to Player 1...\n");
  //TCP Handshake

  char* board=malloc(42*sizeof(char));
  for(int i=0;i<42;i++){
    *(board+i)='_';
  }
  printf("Your token is O\n\n");

  while(checkBoard(board)==0){  //function in main.c
    printf("Player 1 is taking their turn...\n\n");
//read from p1

    if(checkBoard(board)==1){
      printBoard(board);
      printf("Player 1 wins!\n");
      break;
    }

    printBoard(board); //main.c
    int col=0;
    printf("Which column do you want to put a piece in?\n");
    scanf("%d",&col);
    while(updateBoard(board,col)==-1){ //main.c
      printf("Column %d is already filled. Please enter a column with space for a new piece:\n",col);
      scanf("%d",&col);
    }

//send to p1

    if(checkBoard(board)==2){
      printBoard(board);
      printf("You win!\n");
      break;
    }

  }

  return;
}
