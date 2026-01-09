#include "networking.h"


void playerLogic(int server_socket, int playerTurn){ 
  printf("Connecting to Player %d...\n", playerTurn);

  char token;
  int oppositePlayer;
  char* board=malloc(42*sizeof(char));
  for(int i=0;i<42;i++){
    *(board+i)='_';
  }

  if (playerTurn == 1) {
      printf("Your token is X\n\n");
      token = 'X';
      oppositePlayer = 2;
  } elseif (playerTurn == 2) {
      printf("Your token is O\n\n");
      token = 'O';
      oppositePlayer = 1;
  }

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

    printf("Player %d is taking their turn...\n\n", oppositePlayer);

    if(checkBoard(board)==2){
      printBoard(board);
      printf("Player d wins!\n", oppositePlayer);
      break;
    }
  }
}

int main(int argc, char *argv[]) {
  char *IP = "127.0.0.1";
  if (argc > 1) IP = argv[1];
  int sd = client_tcp_handshake(IP);
  if (sd < 0) { printf("connect failed\n"); return 1; }
  printf("connected\n");

  player1Logic(sd);

  close(sd);
  return 0;
}
