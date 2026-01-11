#include "networking.h"

void subserver_logic(int p1_socket,int p2_socket){ //subserver does game, closes when game ends and sends info on who won to server
  int end=0;
  while(end==0){

    int r; //receive
    char rBuff[256];
    int s; //send
    char sBuff[256];

/*
    char str[256];
    int r=recv(player_socket,str,sizeof(str),0);
    if(r==-1){
      printf("%s\n",strerror(errno));
      exit(1);
    }
    if(r==0){
      printf("Socket closed\n\n");
      exit(1);
    }

//    int s=send(client_socket,rot,sizeof(rot),0);
/*
    if(s==-1){
      printf("%s\n",strerror(errno));
      exit(1);
    }
*/
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
    int p1_socket = server_tcp_handshake(listen_socket);
    int p2_socket = server_tcp_handshake(listen_socket);

    printf("server connected.\n");
    int f=fork();
    if(f<0){
      printf("%s\n",strerror(errno));
      exit(1);
    }
    if(f==0){ //subserver
      subserver_logic(player_socket);
    }
    else{ //parent server
      close(player_socket);
    }
  }
}

/*
int main(){
  int listen_socket = server_setup();
  printf("Listening on port %s\n", PORT);
  close(listen_socket);

  return 0;
}
*/
