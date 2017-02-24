
/*
Results generated using the time Linux command 
https://docs.google.com/spreadsheets/d/1IF-P9PNvzW08hUVm_qctiaHZ-c-VFmrax_pP_Rr5SiY/pubchart?oid=1787448230&format=interactive
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_THREADS    16 //Here you define the number of threads you want to create
#define N_POINTS    10000 //Set the number of points you wanna count for all the square


void *CalculatePoints(void *circle_count)
{
	int *count = (int *)circle_count;
	for(int i=0; i<N_POINTS/NUM_THREADS; i++){
		float x, y;
		x = (float)(rand() % 100)/100;

		y = (float)(rand() % 100)/100;

		if(x*x+y*y<1){
			*count=*count+1;
		}

	}
    	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int circle_count = 0;
    int rc;
		int j=0;

		for(; j<NUM_THREADS; j++){
			rc = pthread_create(&threads[j], NULL, CalculatePoints, &circle_count);
			if (rc){
					printf("ERROR; return code from pthread_create() is %d\n", rc);
					exit(-1);
			}
		}

		pthread_join(threads[j-1], NULL);

		printf("Count is: %d\n",circle_count);
			float pi = 4.0*circle_count/N_POINTS;
			printf("PI is: %f",pi);


    pthread_exit(NULL);
}
