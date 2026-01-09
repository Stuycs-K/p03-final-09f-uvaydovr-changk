#include "networking.h"

int server_setup(){
  struct addrinfo * hints;
  struct addrinfo * results;
  hints=calloc(1,sizeof(struct addrinfo));
  hints->ai_family=AF_INET;
  hints->ai_socktype=SOCK_STREAM;
  hints->ai_flags =AI_PASSIVE;
  getaddrinfo(NULL, PORT, hints, &results);

  //create the socket
  int sd = socket(results->ai_family,results->ai_socktype,results->ai_protocol);
  int yes = 1;
  int sockOpt=setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes));
  err(sockOpt,"sockopt  error");

  int b = bind(sd, results->ai_addr, results->ai_addrlen);
  err(b, "bind error");

  int l = listen(sd, 10);
  printf("Server is listening on port %s\n", PORT);
  err(l, "listen error");

  //free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);

  return sd;
}

/*Accept a connection from a client
 *return the socket descriptor for the new socket connected to the client
 *blocks until connection is made.
 */
int server_tcp_handshake(int listen_socket){
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
int client_tcp_handshake(char * server_address){
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
