/*
 * 
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>>

#define NUM_THREADS 4

sem_t semaphore;

void *routine(void *args) {
    sem_wait(&semaphore);
    sleep(1);
    printf("Hello from thread %d\n", *(int*)args);
    sem_post(&semaphore);
    *(int*)args = 5;
    return args;
}

int main()
{
    pthread_t th[NUM_THREADS];

    sem_init(&semaphore, 0, 2);   // initialize semaphore object

    for (int i = 0; i < NUM_THREADS; i++) {
        int *a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) !=0) {
            perror("Failed to create thread");
        }
    }

    for (int j=0; j < NUM_THREADS; j++) {
        int *res;
        if (pthread_join(th[j], (void**)&res) != 0) {
            perror("Failed to join thread");
        }
        printf("Thread %d has finished with result: %d\n", j, *res);
        free(res);
    }

    sem_destroy(&semaphore);

    return 0;
}
