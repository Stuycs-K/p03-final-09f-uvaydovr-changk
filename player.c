#include "networking.h"


void player1Logic(){ // parameter: socket?
  printf("Connecting to Player 2...\n");
  //TCP Handshake

  char* board=malloc(42*sizeof(char));
  for(int i=0;i<42;i++){
    *(board+i)='_';
  }
  printf("Your token is X\n\n");

  while(checkBoard(board)==0){  //function in main.c
    printBoard(board); //main.c
    int col=0;
    printf("Which column do you want to put a piece in?\n");
    scanf("%d",&col);
    while(updateBoard(board,col)==-1){ //main.c
      printf("Column %d is already filled. Please enter a column with space for a new piece:\n",col);
      scanf("%d",&col);
    }

    if(checkBoard(board)==1){
      printBoard(board);
      printf("You win!\n");
      break;
    }

    printf("Player 2 is taking their turn...\n\n");
    //player 2 turn stuff

    if(checkBoard(board)==2){
      printBoard(board);
      printf("Player 2 wins!\n");
      break;
    }
  }
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
   //player 1 turn stuff

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

   if(checkBoard(board)==2){
     printBoard(board);
     printf("You win!\n");
     break;
   }

 }

 return;
}


int main(int argc, char *argv[]) {
  char *IP = "127.0.0.1";
  if (argc > 1) IP = argv[1];
  int sd = client_tcp_handshake(IP);
  if (sd < 0) { printf("connect failed\n"); return 1; }
  printf("connected\n");
  close(sd);
  return 0;
}
