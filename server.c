#include "networking.h"

static void sighandler(int signo){
  if(signo==SIGINT){
    printf("\nSIGINT detected, closing server\n");
    exit(0);
  }

}

//subserver does game, closes when game ends and sends info on who won to server
void subserver_logic(int p1_socket,int p2_socket){
  int buff = 0;
  int r;
  int s;

  buff = 1;
  s=send(p1_socket,&buff,sizeof(buff),0);
  err(s,"send");

  buff = 2;
  s=send(p2_socket,&buff,sizeof(buff),0);
  err(s,"send");

  while(1){
    r=recv(p1_socket,&buff,sizeof(buff),0);
    err(r,"recv");
    if(r==0){
      printf("Connection with Player 1 lost, closing game.\n");
      close(p1_socket);
      return;
    }
    s=send(p2_socket,&buff,sizeof(buff),0);
    err(s,"send");

    r=recv(p2_socket,&buff,sizeof(buff),0);
    err(r,"recv");
    if(r==0){
      printf("Connection with Player 2 lost, closing game.\n");
      close(p2_socket);
      return;
    }
    s=send(p1_socket,&buff,sizeof(buff),0);
    err(s,"send");
  }
}

int main(int argc, char *argv[] ) {
 //Forking
  int listen_socket = server_setup();
  printf("Listening on port %s\n\n", PORT);
  signal(SIGINT, sighandler);

  while(1){
    int p1_socket = server_tcp_handshake(listen_socket);
    int p2_socket = server_tcp_handshake(listen_socket);
    printf("Server connected 2 players.\n\n");

    int f=fork();
    if(f<0){
      printf("%s\n",strerror(errno));
      close(p1_socket);
      close(p2_socket);
      exit(0);
    }
    if(f==0){ //subserver
      close(listen_socket);
      subserver_logic(p1_socket, p2_socket);
      close(p1_socket);
      close(p2_socket);
      exit(0);
    }
    else{ //parent server
      close(p1_socket);
      close(p2_socket);
    }
  }
  close(listen_socket);
}
