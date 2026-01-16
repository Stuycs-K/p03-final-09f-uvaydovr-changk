#include "networking.h"
#include "game.h"

#define MAX_PLAYERS 100
#define NAME_LEN 100

static int game_id = 0;

static void sighandler(int signo){
  if(signo==SIGINT){
    printf(COLOR_RED "[SERVER] SIGINT detected, shutting down.\n" COLOR_RESET);
    exit(0);
  }

}

void leaderboard() {
    FILE *fp = fopen("leaderboard.txt", "r");
    if (!fp) {
        printf(COLOR_RED "[SERVER] No leaderboard yet. Play some games first.\n" COLOR_RESET);
        return;
    }

    char names[MAX_PLAYERS][NAME_LEN];
    int wins[MAX_PLAYERS];
    int count = 0;

    int i = 0;
    while (i < MAX_PLAYERS) {
        wins[i] = 0;
        i++;
    }

    char line[NAME_LEN];
    while(fgets(line, sizeof(line), fp)) {
    	int len = 0;
        while (line[len] != '\0') {
            if (line[len] == '\n') {
                line[len] = '\0';
                break;
            }
            len++;
        }

        if (line[0] == '\0') continue;

        int found = 0;
        int j = 0;

        while (j < count) {
        	if(strcmp(names[j], line) == 0) {
        		wins[j] = wins[j] + 1;
        		found = 1;
        		break;
        	}
        	j++;
        }

        if (!found && count < MAX_PLAYERS) {
        	int k = 0;
        	while (line[k] != '\0' && k < NAME_LEN - 1) {
        		names[count][k] = line[k];
        		k++;
        	}

        	names[count][k] = '\0';
        	wins[count] = 1;
        	count++;
        }
	}

	fclose(fp);

	printf("\n" COLOR_BOLD "=== TOURNAMENT LEADERBOARD ===" COLOR_RESET "\n");
	if (count == 0) {
		printf("(no wins recorded yet) \n\n");
		return;
	}

	int idx = 0;
	while(idx < count) {
		printf("%2d. %-20s  %d wins\n", idx + 1, names[idx], wins[idx]);
		idx++;
	}

	printf("==================================\n\n");
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

  char name1[100];
  char name2[100];

  r = recv(p1_socket, name1, sizeof(name1), 0);
  err(r, "recv name1");

  r = recv(p2_socket, name2, sizeof(name2), 0);
  err(r, "recv name2");

  printf(COLOR_CYAN "[SERVER] Game players: '%s' vs '%s'\n" COLOR_RESET, name1, name2);

  s = send(p1_socket, name2, sizeof(name2), 0);
  err(s, "send opp name to p1");

  s = send(p2_socket, name1, sizeof(name1), 0);
  err(s, "send opp name to p2");

  while(1){
    r=recv(p1_socket,&buff,sizeof(buff),0);
    if(r <= 0){
      printf(COLOR_RED "[SERVER] Connection with Player 1 lost, closing game.\n" COLOR_RESET);
      close(p1_socket);
      return;
    }
    err(r, "recv");

    if(buff == -1) {
        int fd = open("leaderboard.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
        if(fd!=-1){
            int len = 0;
            while (name2[len] != '\0') {
                len++;
            }
            write(fd, name2, len);
            write(fd, "\n", 1);
            close(fd);

            printf(COLOR_GREEN "[SERVER] Game finished. Winner: %s\n" COLOR_RESET, name2);
            leaderboard();
        }

        close(p1_socket);
        close(p2_socket);
        return;
    }



    s=send(p2_socket,&buff,sizeof(buff),0);
    err(s,"send");


    r=recv(p2_socket,&buff,sizeof(buff),0);
    err(r,"recv");
    if(r==0){
      printf(COLOR_RED "[SERVER] Connection with Player 2 lost, closing game.\n" COLOR_RESET);
      close(p2_socket);
      return;
    }


    if(buff == -1) {
        int fd = open("leaderboard.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd != -1) {
            int len = 0;
            while (name1[len] != '\0') {
            	len++;
            }
            write(fd, name1, len);
            write(fd, "\n", 1);
            close(fd);

            printf(COLOR_GREEN "[SERVER] Game finished. Winner: %s\n" COLOR_RESET, name1);
            leaderboard();
        }

        close(p1_socket);
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
  printf(COLOR_BOLD "[SERVER] Listening on port %s\n\n" COLOR_RESET, PORT);
  signal(SIGINT, sighandler);

  while(1){
    printf("[SERVER] Waiting for two players to connect...\n");
    int p1_socket = server_tcp_handshake(listen_socket);
    int p2_socket = server_tcp_handshake(listen_socket);
    printf(COLOR_GREEN "[SERVER] Two players connected. Starting game setup.\n\n" COLOR_RESET);

    game_id = game_id + 1;
    printf(COLOR_BOLD "[SERVER] Starting game %d: waiting for winner...\n\n", game_id);

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
