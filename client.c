#include "networking.h"

void clientLogic(int server_socket){
  int playerTurn;
  recv(server_socket, &playerTurn, sizeof(playerTurn), 0);
  printf("You are Player %d.\n", playerTurn);
  playerLogic(server_socket, playerTurn);
}

int main(int argc, char *argv[] ) {
  char* IP = "127.0.0.1";
  if(argc>1){
    IP=argv[1];
  }
  printf("%s\n",IP);
  int server_socket = client_tcp_handshake(IP);
  printf("client connected.\n\n");
  clientLogic(server_socket);
  close(server_socket);
  return 0;
}
