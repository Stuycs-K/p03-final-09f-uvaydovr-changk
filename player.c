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

  printf(COLOR_CYAN "[PLAYER] Enter your name: " COLOR_RESET);
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

  fd_set read_fds;

  while(1){
/*
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(server_socket,&read_fds);
    int sel = select(server_socket+1, &read_fds, NULL, NULL, NULL);
//    int sel = select(STDIN_FILENO+1, &read_fds, NULL, NULL, NULL);
    err(sel,"select");
*/
    int col = 0;

    char result = checkBoard(board);
    if (result == token) {
      printf("You win!\n");;
      break;
    } else if (result == oppToken) {
      printf("%s (Player %d) wins!\n", oppName, oppositePlayer);

      int winSig = -1;
      int s2 = send(server_socket, &winSig, sizeof(winSig), 0);
      err(s2, "send winner signal:");
      break;
    } else if (result == 'D') {
      printf("Board full. Draw.\n");
      break;
    }

    if (currentTurn == playerTurn) {
      printf("%s, which column do you want to put a piece in?\n", name );

//      if (FD_ISSET(STDIN_FILENO, &read_fds)) { // *
        if(scanf("%d", &col) != 1) {
          printf("That it not a number. Make sure to always enter a valid number. Game ending now.\n");
          return;
        }
//      } // *

      while(updateBoard(board, col, token)==-1){
        if(col>6||col<0){
          printf("Column %d does not exist. Please enter a valid column number:\n",col);

//          if (FD_ISSET(STDIN_FILENO, &read_fds)) {  // ***

          if (scanf("%d", &col) != 1) {
            printf("That it not a number. Make sure to always enter a valid number. Game ending now.\n");
            return;
          }

//          } // ***

        }
        else {
          printf("Column %d is already filled. Please enter a column with space for a new piece:\n",col);\

//          if (FD_ISSET(STDIN_FILENO, &read_fds)) {  // ***

          if (scanf("%d", &col) != 1) {
            return;
          }

//          } // ***

        }

      }
      sBuff=col;
      int s=send(server_socket,&sBuff,sizeof(sBuff),0);
      err(s,"send error");
    }

    else {
      printf("%s (Player %d) is taking their turn...\n\n", oppName, oppositePlayer);

//  if (FD_ISSET(server_socket, &read_fds)) {  // **
      int r=recv(server_socket, &rBuff,sizeof(rBuff),0);

      printf("received %d bytes:",r);
      printf("%d\n",rBuff);

      if(r==0){
        printf("Connection with %s (Player %d) has ended, closing game\n",oppName, oppositePlayer);
        return;
      }
      err(r,"recv error");
//  } // **
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
  printf("Connected to server\n\n");

  int playerTurn = 0;
  int r = recv(sd, &playerTurn, sizeof(playerTurn), 0);

  if (r <= 0) {
    printf("Server closed before assigning player number\n");
    close(sd);
    return 1;
  }
  printf("You are Player %d \n", playerTurn);
  playerLogic(sd,playerTurn);

  close(sd);

  return 0;
}
