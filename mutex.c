/*
 * Solve the race condition using a mutex. The mutex ensures the
 * critical section is only run by one thread at a time.
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define BIG_NUM 100000000
#define NUM_THREADS 4

int mails = 0;
pthread_mutex_t mutex;                  // declare mutex object

void *routine()
{
    for (int i=0; i < BIG_NUM; i++) {
        pthread_mutex_lock(&mutex);     // lock the critical section
        mails++;
        pthread_mutex_unlock(&mutex);   // unlock the critical section
    }
}

int main()
{
    pthread_t th[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);   // initialize mutex object

    for (int i=0; i < NUM_THREADS; i++) {
        if (pthread_create(&th[i], NULL, &routine, NULL) !=0) {
            printf("Failed to create thread: %d\n", i);
            return -1;
        }
        printf("Thread %d has started\n", i);
    }

    for (int i=0; i < NUM_THREADS; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            printf("Failed to join thread: %d\n", i);
            return -2;
        }
        printf("Thread %d has finisHed\n", i);
    }

    pthread_mutex_destroy(&mutex);      // free mutex from memory

    printf("Number of mails: %d\n", mails);
    printf("mails is equal correct: %d\n", mails == NUM_THREADS*BIG_NUM);
    return 0;
}
