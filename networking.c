#include "networking.h"

/*Create and bind a socket.
* Place the socket in a listening state.
* returns the socket descriptor
*/
int server_setup(){ // run twice, once for each player
  //setup structs for getaddrinfo
  struct addrinfo * hints;
  struct addrinfo * results;
  hints=calloc(1,sizeof(struct addrinfo));
  hints->ai_family=AF_INET;
  hints->ai_socktype=SOCK_STREAM; //TCP socket
  hints->ai_flags =AI_PASSIVE;
  getaddrinfo(NULL, PORT, hints, &results); //Server sets node to NULL

  //create two sockets
  int playerd;//store the socket descriptor here
  playerd=socket(results->ai_family,results->ai_socktype,results->ai_protocol);

  //this code should get around the address in use error
  int yes = 1;
  int sockOpt=setsockopt(playerd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes));
  err(sockOpt,"sockopt  error");

  //bind the socket to address and port
  if(bind(playerd,results->ai_addr,results->ai_addrlen)==-1){
    printf("Bind error, errno: %s\n",strerror(errno));
    exit(1);
  }

  //set socket to listen state
  if(listen(playerd,1)==-1){
    printf("%s\n",strerror(errno));
    exit(1);
  }

  //free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);

  return playerd;
}

/*Accept a connection from a client
 *return the socket descriptor for the new socket connected to the client
 *blocks until connection is made.
 */
int server_tcp_handshake(int listen_socket){ //run twice, once for each player
    int player_socket;
    struct sockaddr_storage add;
    socklen_t size=sizeof(add);

    //accept() the player connection
    player_socket=accept(listen_socket,(struct sockaddr *) &add,&size); //Blocks until connection
    if(player_socket==-1){
      printf("Server Accept Error: %s\n",strerror(errno));
      exit(1);
    }

    return player_socket;
}

/*Connect to the server
 *return the to_server socket descriptor
 *blocks until connection is made.*/
int player_tcp_handshake(char * server_address){ //both players do this with server
  //getaddrinfo
  struct addrinfo * hints;
  struct addrinfo * results;
  hints=calloc(1,sizeof(struct addrinfo));
  hints->ai_family=AF_INET;
  hints->ai_socktype=SOCK_STREAM;
  int info = getaddrinfo(server_address, PORT, hints, &results);

  if (info != 0) {
  	free(hints);
  	return -1;
  }

  int serverd = socket(results->ai_family,results->ai_socktype,results->ai_protocol);
  if (serverd < 0) {
  	perror("socket");
    free(hints);
    freeaddrinfo(results);
    return -1;
  }

  //connect() to the server
  int c = connect(serverd, results->ai_addr, results->ai_addrlen);
  err(c, "connect");

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
