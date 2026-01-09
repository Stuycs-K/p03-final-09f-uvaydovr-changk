#include "networking.h"

void clientLogic(int server_socket){
  int end=0;
  while(end==0){
    char str[256];
    printf("Input text to send to server:\n");
    if(fgets(str,sizeof(str),stdin)==NULL){
      printf("Client closed\n");
      exit(1);
    }
    str[strlen(str)-1]='\0';

    //sends to server
    int s=send(server_socket,str,sizeof(str),0);
    if(s==-1){
      printf("%s\n",strerror(errno));
      exit(1);
    }

    //read rot
    char rot[256];
    int r=recv(server_socket,rot,sizeof(rot),0); //sizeof
    if(r==-1){
      printf("%s\n",strerror(errno));
      exit(1);
    }
    if(r==0){
      printf("Socket closed\n");
      exit(1);
    }
    printf("Rotated strings:\n%s\n\n",rot);
  }
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
