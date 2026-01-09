#include "networking.h"
int main(void) {
  int listen_socket = server_setup();
  printf("Listening on port %s\n", PORT);
  close(listen_socket);
  return 0;
}
