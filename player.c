#include "networking.h"
#include "main.h"

void playerLogic(int server_socket, int playerTurn){
  char token;
  char oppToken;
  int oppositePlayer;

  char board[BOARD_SIZE];
  for (int i = 0; i < BOARD_SIZE; i++) {
    board[i] = '_';
  }

  if (playerTurn == 1) {
      printf("Your token is X\n\n");
      token = 'X';
      oppToken = 'O';
      oppositePlayer = 2;
  } else if (playerTurn == 2) {
      printf("Your token is O\n\n");
      token = 'O';
      oppToken = 'X';
      oppositePlayer = 1;
  }

  int r; //receive
  int* rBuff=malloc(sizeof(int));
  int s; //send
  int* sBuff=malloc(sizeof(int));

  printf("Connecting to Player %d...\n", oppositePlayer);
  r = recv(server_socket,rBuff,sizeof(rBuff),0);
  err(r, "recv");
  printf("Connected to Player %d!\n\n", oppositePlayer);

  int col=0;

  int currentTurn = 1;
  while(1){
    printBoard(board); //main.c

    int status = checkBoard(board);  //function in main.c
    if (status == 1) {
      printf("You win! \n");
      break;
    } else if (status == 2) {
      printf("Player %d wins!\n", oppositePlayer);
      break;
    } else if (status == -1) {
      printf("Board full. Draw.\n");
      break;
    }

    if (currentTurn == playerTurn) {
      int col;
      printf("Which column do you want to put a piece in?\n");
      scanf("%d",&col);

      while(updateBoard(board,col, token)==-1){ //main.c
        printf("Column %d is already filled. Please enter a column with space for a new piece:\n",col);
        scanf("%d",&col);
      }

      *sBuff=col;
      s=send(server_socket,(char *) sBuff,sizeof(sBuff),0);
      err(s,"send error");
    } else {
      printf("Player %d is taking their turn...\n\n", oppositePlayer);
      r=recv(server_socket,(char *) rBuff,sizeof(rBuff),0);
      err(r,"recv error");
      col=*rBuff;
      updateBoard(board,col, oppToken);
    }

    if (currentTurn == 1) {
      currentTurn = 2;
    } else {
      currentTurn = 1;
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
  printf("Connected to server\n\n");

  playerLogic(sd,pNum);

  close(sd);

  return 0;
}
