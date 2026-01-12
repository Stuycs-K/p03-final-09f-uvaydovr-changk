#include "networking.h"
#include "main.h"

void playerLogic(int server_socket, int playerTurn){
  char token;
  char opp_token;
  int oppositePlayer;

  char board[BOARD_SIZE];
  for (i = 0; i < BOARD_SIZE; i++) {
    board[i] = '_';
  }

  if (playerTurn == 1) {
      printf("Your token is X\n\n");
      token = 'X';
      opp_token = 'O';
      oppositePlayer = 2;
  } else if (playerTurn == 2) {
      printf("Your token is O\n\n");
      token = 'O';
      opp_token = 'X';
      oppositePlayer = 1;
  }

  int r; //receive
  int* rBuff=malloc(sizeof(int));
  int s; //send
  int* sBuff=malloc(sizeof(int));

  printf("Connecting to Player %d...\n", oPlayer);
  r = recv(server_socket,rBuff,sizeof(rBuff),0);
  err(r, "recv");
  printf("Connected to Player %d!\n\n", oPlayer);

  int col=0;
  int check=checkBoard(board); //0

  while(check == 0){  //function in main.c
    if(playerTurn == 1){
      printBoard(board); //main.c
      printf("Which column do you want to put a piece in?\n");
      scanf("%d",&col);

      while(updateBoard(board,col)==-1){ //main.c
        printf("Column %d is already filled. Please enter a column with space for a new piece:\n",col);
        scanf("%d",&col);
      }

      *sBuff=col;
      s=send(server_socket,(char *) sBuff,sizeof(sBuff),0);
      err(s,"send error");

      printf("Player %d is taking their turn...\n\n", oPlayer);
      r=recv(server_socket,(char *) rBuff,sizeof(rBuff),0);
      err(r,"recv error");
      col=*rBuff;
      updateBoard(board,col);
    }


    else{  //p2
      printf("Player %d is taking their turn...\n\n", oPlayer);
      r=recv(server_socket,(char *) rBuff,sizeof(rBuff),0);
      err(r,"recv error");
      col=*rBuff;
      updateBoard(board,col);

      printBoard(board); //main.c
      printf("Which column do you want to put a piece in?\n");
      scanf("%d",&col);
      while(updateBoard(board,col)==-1){ //main.c
        printf("Column %d is already filled. Please enter a column with space for a new piece:\n",col);
        scanf("%d",&col);
      }

      *sBuff=col;
      s=send(server_socket,(char *) sBuff,sizeof(sBuff),0);
      err(s,"send error");
    }

    check=checkBoard(board);
  }

  if(check==playerTurn){
    printf("You win!");
  }
  else{
    printf("Player %d wins!",oPlayer);
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
  printf("Connected to server\n\n");

  playerLogic(sd,pNum);

  close(sd);

  return 0;
}
