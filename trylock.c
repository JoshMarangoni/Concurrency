/*
 * Solve the race condition using a mutex. The mutex ensures the
 * critical section is only run by one thread at a time.
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define BIG_NUM 100000000
#define NUM_THREADS 4

pthread_mutex_t mutex;                  // declare mutex object

void *routine()
{
    if (pthread_mutex_trylock(&mutex) == 0) {   // try to get the lock
        printf("Got lock\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);   // unlock the critical section
    } else {
        printf("Didn't get lock\n");
    }
}

int main()
{
    pthread_t th[NUM_THREADS];

    int *res;   // will be used as double pointer for returning result
                // of threads

    pthread_mutex_init(&mutex, NULL);   // initialize mutex object

    for (int i=0; i < NUM_THREADS; i++) {
        if (pthread_create(&th[i], NULL, &routine, NULL) !=0) {
            perror("Failed to create thread\n");
        }
    }

    for (int i=0; i < NUM_THREADS; i++) {
        if (pthread_join(th[i], (void**)&res) != 0) {
            perror("Failed to join thread\n");
        }
    }

    pthread_mutex_destroy(&mutex);      // free mutex from memory

    return 0;
}
