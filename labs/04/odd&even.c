//Count the number of odd and even numbers given in an array

#include <time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int totalOdd = 0 ;
int totalEven = 0;
int array[] = {55,106,98,976,36,87,88,99,87,34,23,7,34455,2,8,9,5,66,77,88,99,100,1,12,33,45,9,87,2,3,4,5,67,45,4,3,212,3434,23,112,1234,7564};
int numberOfThreads =1; //modify the number of threads to use

void *count(int initIndex){
  int i;
  size_t size = sizeof array / sizeof array[0];
  for (i = initIndex; i < initIndex+((int) size/numberOfThreads); i++){
       if (array[i] % 2 == 0)
       {
         totalEven++;
           printf("Even: %d\n",array[i]);
       }
       else{
         printf("Odd: %d\n",array[i]);
         totalOdd++;
       }
   }
}

void main(int argc, char *argv[]){
        clock_t start, end;
        double cpu_time_used;
        start = clock();
        pthread_t threads[numberOfThreads];
        size_t size = sizeof array / sizeof array[0];
        int i;
        for(i=0; i<numberOfThreads; i++){
          printf("enr: %d\n");
                pthread_create(&threads[i],NULL,count,((int) size/numberOfThreads)*i);
                pthread_join(threads[i],NULL);
        }
        end = clock();

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        printf("Odd numbers: %d\n",totalOdd);
        printf("Even numbers: %d\n",totalEven);
        printf("CPU time used: %f\n",cpu_time_used);

}
