#include <unistd.h>   
#include <sys/types.h>  
#include <errno.h>     
#include <stdio.h>     
#include <stdlib.h>     
#include <pthread.h>    
#include <string.h>     
#include <semaphore.h>  
#include <sys/shm.h>

void handler ( void *ptr );
int *p;
key_t shmkey;               
int shmid;
sem_t mutex;


int main()
{
  shmkey = ftok ("/dev/null", 5);       
    shmid = shmget (shmkey, sizeof (int), 0644 | IPC_CREAT);
    if (shmid < 0){                          
        perror ("shmget\n");
        exit (1);
    }

    p = (int *) shmat (shmid, NULL, 0); 
    *p = 50;
 
    int i[4];
    pthread_t thread_a;
    pthread_t thread_b;
 pthread_t thread_c;
    pthread_t thread_d;
    
    i[0] = 1;
    i[1] = 2;
 i[2] = 3;
    i[3] = 4;
    
    sem_init(&mutex, 0, 1);      
                                                                 
    pthread_create (&thread_a, NULL, (void *) &handler, (void *) &i[0]);
    pthread_create (&thread_b, NULL, (void *) &handler, (void *) &i[1]);
pthread_create (&thread_c, NULL, (void *) &handler, (void *) &i[2]);
    pthread_create (&thread_d, NULL, (void *) &handler, (void *) &i[3]);
    
    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
pthread_join(thread_c, NULL);
    pthread_join(thread_d, NULL);

    sem_destroy(&mutex); 
                  

    exit(0);
} 

void handler ( void *ptr )
{
    int x = *((int *) ptr);
   printf ("Cashier %d: Welcome to the dairy \"The cow that laughs\"\n",x);
    printf("Cashier %d: Waiting to retrieve availability...\n",x);
    sem_wait(&mutex); 
    if(*p > 0 ){
    printf("Cashier %d: You're lucky. Still remains %d lts\n", x, *p);
    printf ("Cashier %d: *PRESS ENTER TO BUY A LITER*\n",x);
    getchar ();
   *p -= 1;
    printf ("Cashier %d: Thanks for buying milk with us\n",x);
    }else{

    printf ("Cashier %d: Sorry, we don't have milk. Come again tomorrow.\n", x);
    }  
    sem_post(&mutex);     
    
    pthread_exit(0); 
}

