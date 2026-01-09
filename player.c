#include "networking.h"
int main(int argc, char *argv[]) {
  char *IP = "127.0.0.1";
  if (argc > 1) IP = argv[1];
  int sd = client_tcp_handshake(IP);
  if (sd < 0) { printf("connect failed\n"); return 1; }
  printf("connected\n");
  close(sd);
  return 0;
}
