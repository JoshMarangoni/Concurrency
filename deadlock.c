/*
 * Solve the race condition using a mutex. The mutex ensures the
 * critical section is only run by one thread at a time.
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define BIG_NUM 1000000
#define NUM_THREADS 4

int mails = 0;
pthread_mutex_t mutex;                  // declare mutex object

void *routine()
{
    for (int i=0; i < BIG_NUM; i++) {
        pthread_mutex_lock(&mutex);     // lock the critical section
        pthread_mutex_lock(&mutex);     // this will cause deadlock
        mails++;
        pthread_mutex_unlock(&mutex);   // unlock the critical section
    }
    int *res = malloc(sizeof(int));
    *res = 0;
    return (void*) res;
}

int main()
{
    pthread_t th[NUM_THREADS];

    int *res;   // will be used as double pointer for returning result
                // of threads

    pthread_mutex_init(&mutex, NULL);   // initialize mutex object

    for (int i=0; i < NUM_THREADS; i++) {
        if (pthread_create(&th[i], NULL, &routine, NULL) !=0) {
            printf("Failed to create thread: %d\n", i);
            return -1;
        }
        printf("Thread %d has started\n", i);
    }

    for (int i=0; i < NUM_THREADS; i++) {
        if (pthread_join(th[i], (void**)&res) != 0) {
            printf("Failed to join thread: %d\n", i);
            return -2;
        }
        printf("Thread %d has finished with result: %d\n", i, *res);
        free(res);
    }

    pthread_mutex_destroy(&mutex);      // free mutex from memory

    printf("Number of mails: %d\n", mails);
    printf("mails is equal correct: %d\n", mails == NUM_THREADS*BIG_NUM);
    return 0;
}
