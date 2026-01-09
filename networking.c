#include "networking.h"

/*Create and bind a socket.
* Place the socket in a listening state.
* returns the socket descriptor
*/
int server_setup(){
  //setup structs for getaddrinfo
  struct addrinfo * hints;
  struct addrinfo * results;
  hints=calloc(1,sizeof(struct addrinfo));
  hints->ai_family=AF_INET;
  hints->ai_socktype=SOCK_STREAM; //TCP socket
  hints->ai_flags =AI_PASSIVE;
  getaddrinfo(NULL, "9845", hints, &results); //Server sets node to NULL

  //create two sockets
  int p1d;//store the socket descriptor here
  int p2d;
  p1d=socket(results->ai_family,results->ai_socktype,results->ai_protocol);
  p2d=socket(results->ai_family,results->ai_socktype,results->ai_protocol);

  //this code should get around the address in use error
  int yes = 1;
  int sockOpt=setsockopt(clientd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes));
  err(sockOpt,"sockopt  error");

  //bind the socket to address and port
  if(bind(p1d,results->ai_addr,results->ai_addrlen)==-1){
    printf("%s\n",strerror(errno));
    exit(1);
  }
  if(bind(p2d,results->ai_addr,results->ai_addrlen)==-1){
    printf("%s\n",strerror(errno));
    exit(1);
  }

  //set socket to listen state
  if(listen(p1d,1)==-1){
    printf("%s\n",strerror(errno));
    exit(1);
  }
  if(listen(p1d,2)==-1){
    printf("%s\n",strerror(errno));
    exit(1);
  }

  //free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);
// setup returns sockets for both players? or run server_setup() twice?
  return p1d;
}

/*Accept a connection from a client
 *return the socket descriptor for the new socket connected to the client
 *blocks until connection is made.
 */
int server_tcp_handshake(int listen_socket){ //server does this for each player
    int client_socket;
    struct sockaddr_storage add;
    socklen_t size=sizeof(add);

    //accept() the client connection
    client_socket=accept(listen_socket,(struct sockaddr *) &add,&size); //Blocks until connection
    if(client_socket==-1){
      printf("Server Accept Error: %s\n",strerror(errno));
      exit(1);
    }

    return client_socket;
}

/*Connect to the server
 *return the to_server socket descriptor
 *blocks until connection is made.*/
int client_tcp_handshake(char * server_address){ //both players do this with server
  //getaddrinfo
  struct addrinfo * hints;
  struct addrinfo * results;
  hints=calloc(1,sizeof(struct addrinfo));
  hints->ai_family=AF_INET;
  hints->ai_socktype=SOCK_STREAM; //TCP socket
//  hints->ai_flags =AI_PASSIVE; //Only for server?
  getaddrinfo(server_address, "9845", hints, &results); //Server sets node to NULL

  int serverd;//store the socket descriptor here
  //create the socket
  serverd=socket(results->ai_family,results->ai_socktype,results->ai_protocol);

  //connect() to the server
  if(connect(serverd,results->ai_addr,results->ai_addrlen)==-1){
    printf("connect() error: %s\n",strerror(errno));
    exit(1);
  }

  free(hints);
  freeaddrinfo(results);

  return serverd;
}

void err(int i, char*message){
  if(i < 0){
	  printf("Error: %s - %s\n",message, strerror(errno));
  	exit(1);
  }
}
