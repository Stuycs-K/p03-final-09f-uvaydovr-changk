#include "main.h"

union semun {
  int val;
  struct semid_ds *buf;
  unsigned short *array;
  struct seminfo *__buf;
};


static void create_all() {
  int semd = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  if (semd == -1) {
    perror("semget");
    exit(1);
  }

  //initialize semaphore value to 1
  union semun us;
  us.val = 1;
  if (semctl(semd, 0, SETVAL, us) == -1) {
    perror("semctl SETVAL");
    exit(1);
  }

  //gets shared memory that can be read/written to
  int shmid = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0600);
  if (shmid == -1) {
    perror("shmget");
    exit(1);
  }

  
  printf("Created semaphore + shared memory. Player 1 starts.\n");
}

static void view() {
  FILE *f = fopen("board.txt", "r");
  if (!f) {
    perror("fopen board.txt");
    return;
  }
  char buf[1024];

  while (fgets(buf, sizeof(buf), f)) {
    fputs(buf, stdout);
  }

  fclose(f);
}


//shmid is shared memory id
//semd is semaphore id btw

static void remove_all() {
  view();
  int shmid = shmget(SHM_KEY, sizeof(int), 0);
  if (shmid != -1) {
    if (shmctl(shmid, IPC_RMID, 0) == -1) {
      perror("shmctl");
    } else {
      printf("\nRemoved shared memory\n");
    }
  } else {
    perror("shmget");
  }

  int semd = semget(SEM_KEY, 1, 0);
  if (semd != -1) {
    if (semctl(semd, 0, IPC_RMID) == -1) {
      perror("semctl");
    } else {
      printf("\nRemoved semaphore\n");
    }
  } else {
    perror("semget");
  }
}


int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("usage: %s [create|view|remove]\n", argv[0]);
    return 1;
  }
  if (strcmp(argv[1], "create") == 0) {
    create();
  }
  if (strcmp(argv[1], "remove") == 0) {
    remove_all();
  }
  if (strcmp(argv[1], "view") == 0) {
    view();
  }

  return 0;
}
