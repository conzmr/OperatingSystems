#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define SHMSZ 27
char SEM_NAME[]= "sem";

int main()
{
  char ch;
  int shmid;
  key_t key;
  char *shm,*s;
  sem_t *mutex;

  key = 1000;
  
  mutex = sem_open(SEM_NAME,0,0644,4);
  if(mutex == SEM_FAILED)
    {
      perror("reader:unable to execute semaphore");
      sem_close(mutex);
      exit(-1);
    }

  shmid = shmget(key,SHMSZ,0666);
  if(shmid<0)
    {
      perror("reader:failure in shmget");
      exit(-1);
    }

  shm = shmat(shmid,NULL,0);

    s = shm;
    printf ("Welcome to the dairy \"The cow that laughs\"\n");
    printf("Cashier waiting to retrieve availability...\n");
    sem_wait(mutex); 
    if(*s > 0 ){
    printf("You're lucky. Still remains %d lts\n", *s);
    printf ("Press enter to buy a liter\n");
    getchar ();
    *shm=*s-1;
    printf ("Thanks for buying milk with us\n");
    }else{
    printf("Sorry, we don't have milk. Come again tomorrow.\n");
    }
    sem_post(mutex);
	

  sem_close(mutex);
  shmctl(shmid, IPC_RMID, 0);
  exit(0);
}

