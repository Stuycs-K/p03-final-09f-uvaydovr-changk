#include "networking.h"
#include "game.h"


static void sighandler(int signo){
  if(signo==SIGINT){
    printf(COLOR_RED "[PLAYER] SIGINT detected, closing game." COLOR_RESET "\n");
    exit(0);
  }
}

void playerLogic(int server_socket, int playerTurn){
  char token;
  char oppToken;
  int oppositePlayer;

  char board[BOARD_SIZE];
  for (int i = 0; i < BOARD_SIZE; i++) {
    board[i] = '_';
  }

  char name[100];
  char oppName[100];

  printf("[PLAYER] Enter your name: ");
  scanf("%s", name);

  int s=send(server_socket, name,sizeof(name),0);
  err(s, "send name");

  int r = recv(server_socket, oppName, sizeof(oppName), 0);
  err(r, "recv name");

  printf(COLOR_CYAN "[PLAYER] Your opponent is %s. \n" COLOR_RESET, oppName);


  if (playerTurn == 1) {
      printf("[PLAYER] You are " COLOR_RED "Player 1 (X)" COLOR_RESET "\n\n");
      token = 'X';
      oppToken = 'O';
      oppositePlayer = 2;
  } else if (playerTurn == 2) {
      printf("[PLAYER] You are " COLOR_YELLOW "Player 2 (0)" COLOR_RESET "\n\n");
      token = 'O';
      oppToken = 'X';
      oppositePlayer = 1;
  }

  int rBuff = 0;
  int sBuff = 0;
  int currentTurn = 1;

  signal(SIGINT,sighandler);

  while(1){
    int col = 0;
    printBoard(board); //main.c

    char result = checkBoard(board);  //function in main.c
    if (result == token) {
      printf(COLOR_GREEN "You win!\n" COLOR_RESET);
      break;
    } else if (result == oppToken) {
      printf(COLOR_RED "%s (Player %d) wins!\n" COLOR_RESET, oppName, oppositePlayer);
      
      int winSig = -1;
      int s2 = send(server_socket, &winSig, sizeof(winSig), 0);
      err(s2, "send winner signal:");
      break;
    } else if (result == 'D') {
      printf(COLOR_RED "Board full. Draw.\n" COLOR_RESET);
      break;
    }

    if (currentTurn == playerTurn) {
      printf("%s, choose a column (0-%d) to drop your piece: ", name, COLS - 1);

      if(scanf("%d", &col) != 1) {
       printf(COLOR_RED "[PLAYER] That is not a number. Please restart and enter valid input.\n" COLOR_RESET);
        return;
      }

      while(updateBoard(board, col, token)==-1){ //main.c

        if(col>6||col<0){
         printf(COLOR_RED "[PLAYER] Column %d does not exist." COLOR_RESET "Enter a valid column number (0-%d):\n", col, COLS - 1);;
          if (scanf("%d", &col) != 1) {
            printf(COLOR_RED "[PLAYER] That it not a number. Make sure to always enter a valid number. Game ending now.\n" COLOR_RESET);
            return;
          }
        } else {
          printf(COLOR_RED "[CLIENT] Column %d is full." COLOR_RESET "Choose a different column: .n", col);
          if (scanf("%d", &col) != 1) {
            return;
          }
      }

      }

      sBuff=col;
      int s=send(server_socket,&sBuff,sizeof(sBuff),0);
      err(s,"send error");
    }

    else {
      printf("[PLAYER] %s (Player %d) is taking their turn...\n\n", oppName, oppositePlayer);
      int r=recv(server_socket, &rBuff,sizeof(rBuff),0);
      if(r==0){
        printf(COLOR_RED "[PLAYER] Connection with %s (Player %d) has ended, closing game\n" COLOR_RESET,oppName, oppositePlayer);
        return;
      }
      err(r,"recv error");

      col=rBuff;
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
  signal(SIGINT, sighandler);
  int sd = player_tcp_handshake(IP);
  if (sd < 0) { printf("connect failed\n"); return 1; }
  printf(COLOR_GREEN "[PLAYER] Connected to server.\n\n" COLOR_RESET);

  int playerTurn = 0;
  int r = recv(sd, &playerTurn, sizeof(playerTurn), 0);

  if (r <= 0) {
    printf(COLOR_RED "[CLIENT] Server closed before assigning player number.\n" COLOR_RESET);
    close(sd);
    return 1;
  }
  
  playerLogic(sd,playerTurn);

  close(sd);

  return 0;
}
