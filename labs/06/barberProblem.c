#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

const int chairs = 5; //numberOfChairs in waiting room
int waitingClients = 0;
int clientId = 0;

sem_t clients;
sem_t barber;
sem_t mutex;

void* pthBarber();
void* pthClient(int *param);
double ramdomTime();


int main() {

    sem_init(&clients, 1, 0);
    sem_init(&barber, 1, 0);
    sem_init(&mutex, 1, 1);
    
    srand(time(NULL));

    pthread_t tBarber, tClient;

    pthread_create(&tBarber, NULL, (void *) pthBarber, NULL);


    while (1) {
        clientId++;
        pthread_create(&tClient, NULL, (void *) pthClient, &clientId);
        sleep(ramdomTime());
    }

    return 0;
}

void* pthClient(int *param) {
  
    sem_wait(&mutex);

    if (waitingClients < chairs) {
	waitingClients++;
        printf("\nA new customer has arrived. There are currently %d clients in the waiting room.\n", (*clients.__size)+1);
        sem_post(&clients); 
        sem_post(&mutex);
        sem_wait(&barber);
    }
    else {
        sem_post(&mutex);
        printf("The waiting room is full, so customer %d left.\n", *param);
    }
    pthread_exit(NULL);
}


void* pthBarber() {
    while(1) {

        sem_wait(&clients);
        sem_wait(&mutex);
        
        waitingClients--;
        
        sem_post(&barber);
        sem_post(&mutex);
        
        printf("The barber is attending a client. There are %d customers in the waiting room.\n", waitingClients);
        
	sleep(3);
    }

    pthread_exit(NULL);
}


double ramdomTime() {
    double res;
    do {
      res = 1.0 + 1.5 * sqrt(-2 * log((rand()+1.0) / (RAND_MAX+1.0))) * cos(2 * M_PI * (rand()+1.0) / (RAND_MAX+1.0));
    }
    while (res <= 1.0 || res >= 3.0);
    return res;
}
