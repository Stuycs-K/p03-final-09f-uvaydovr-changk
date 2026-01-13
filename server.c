#include "networking.h"

static void sighandler(int signo){
  if(signo==SIGINT){
    printf("\nSIGINT detected, closing server\n");
  }
  exit(0);
}

void subserver_logic(int p1_socket,int p2_socket){ //subserver does game, closes when game ends and sends info on who won to server
  int buff = 0;
  int r;
  int s;
  s=send(p1_socket,&buff,sizeof(buff),0);
  err(s,"send");
  s=send(p2_socket,&buff,sizeof(buff),0);
  err(s,"send");

  while(1){
    r=recv(p1_socket,&buff,sizeof(buff),0);
    err(r,"recv");
    if(r==0){
      printf("Connection closed\n");
      return;
    }
    s=send(p2_socket,&buff,sizeof(buff),0);
    err(s,"send");

    r=recv(p2_socket,&buff,sizeof(buff),0);
    err(r,"recv");
    if(r==0){
      printf("Connection closed\n");
      return;
    }
    s=send(p1_socket,&buff,sizeof(buff),0);
    err(s,"send");
  }
}

int main(int argc, char *argv[] ) {
  //Not forking
/*
  int listen_socket = server_setup();
  int client_socket = server_tcp_handshake(listen_socket);
  printf("server connected.\n");
  subserver_logic(client_socket);
*/

 //Forking
  int listen_socket = server_setup();
  printf("Listening on port %s\n\n", PORT);
//printf("%d\n",listen_socket);
  while(1){
    signal(SIGINT,sighandler);
//    int p1_socket;
//    int p2_socket;
    int p1_socket = server_tcp_handshake(listen_socket); //figure out how to determine which is p1 and p2, right now it's just whoever goes first
    int p2_socket = server_tcp_handshake(listen_socket); // ***
    printf("server connected 2 players.\n\n");

    int f=fork();
    if(f<0){
      printf("%s\n",strerror(errno));
      close(p1_socket);
      close(p2_socket);
      exit(1);
    }
    if(f==0){ //subserver
      close(listen_socket);
      subserver_logic(p1_socket, p2_socket);
      close(p1_socket);
      close(p2_socket);
    }
    else{ //parent server
      close(p1_socket);
      close(p2_socket);
    }
  }
  close(listen_socket);
}
