#include "networking.h"
#include "main.h"

void playerLogic(int server_socket, int playerTurn){
  char token;
  int oPlayer;
  char* board=malloc(42*sizeof(char));
  for(int i=0;i<42;i++){
    *(board+i)='_';
  }

  if(playerTurn == 1){
    oPlayer = 2;
  }
  else{
    oPlayer = 1;
  }

  int r; //receive
  char rBuff[256];
  int s; //send
  char sBuff[256];

  printf("Connecting to Player %d...\n", oPlayer);
  r=recv(server_socket,rBuff,sizeof(rBuff),0);
  err(r, "recv");

  if(playerTurn==1){
    printf("Your token is X\n\n");
    token = 'X';
  }
  if(playerTurn==2){
    printf("Your token is O\n\n");
    token = 'O';
  }

  while(checkBoard(board)==0){  //function in main.c
    if(playerTurn==1){
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

      printf("Player %d is taking their turn...\n\n", oPlayer);
    }
    else{  //p2
      if(checkBoard(board)==2){
        printBoard(board);
        printf("Player %d wins!\n", oPlayer);
        break;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  char *IP = "127.0.0.1";
  int pNum=0;
  if(argc==1){
    printf("Add argument '1' to be Player 1\n");
    printf("Add argument '2' to be Player 2\n");
    return -1;
  }
  pNum=(int) strtol(argv[1],NULL,10);
//printf("%d\n",pNum);
  int sd = player_tcp_handshake(IP);

  if (sd < 0) { printf("connect failed\n"); return 1; }
  printf("connected\n");

  playerLogic(sd,pNum);

  close(sd);

  return 0;
}
