#include "networking.h"

void subserver_logic(int p1_socket,int p2_socket){ //subserver does game, closes when game ends and sends info on who won to server
  int r; //receive
  int s; //send
  int* buff=malloc(sizeof(int));

  s=send(p1_socket,buff,sizeof(buff),0);
  s=send(p2_socket,buff,sizeof(buff),0);

  int end=0;
  while(end==0){
    r=recv(p1_socket,(char *) buff,sizeof(buff),0);
    err(r,"recv error");
//    printf("col: %d\n",*buff);
    s=send(p2_socket,(char *) buff,sizeof(buff),0);
    err(s,"send error");

    r=recv(p2_socket,(char *) buff,sizeof(buff),0);
    err(r,"recv error");
//    printf("col: %d\n",*buff);
    s=send(p1_socket,(char *) buff,sizeof(buff),0);
    err(s,"send error");
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
//printf("%d\n",listen_socket);
  int end=0;
  while(end==0){
    int p1_socket = server_tcp_handshake(listen_socket); //figure out how to determine which is p1 and p2, right now it's just whoever goes first
    int p2_socket = server_tcp_handshake(listen_socket);

    printf("server connected.\n");
    int f=fork();
    if(f<0){
      printf("%s\n",strerror(errno));
      exit(1);
    }
    if(f==0){ //subserver
      subserver_logic(p1_socket,p2_socket);
    }
    else{ //parent server
      close(p1_socket);
      close(p2_socket);
    }
  }
}
