/*
 * Solve the race condition using a mutex. The mutex ensures the
 * critical section is only run by one thread at a time. One of the
 * drawbacks of mutexes is they are typically slower.
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define BIG_NUM 1000000000

int mails = 0;
pthread_mutex_t mutex;   // declare mutex object

void *routine()
{
    for (int i=0; i < BIG_NUM; i++) {
        pthread_mutex_lock(&mutex);    // lock the critical section
        mails++;
        pthread_mutex_unlock(&mutex);  // unlock the critical section
    }
}

int main()
{
    pthread_t t1, t2;

    pthread_mutex_init(&mutex, NULL);   // initialize mutex object

    if (pthread_create(&t1, NULL, &routine, NULL) !=0) return 1;
    if (pthread_create(&t2, NULL, &routine, NULL) !=0) return 2;
    if (pthread_join(t1, NULL) != 0) return 3;
    if (pthread_join(t2, NULL) != 0) return 4;

    pthread_mutex_destroy(&mutex);      // free mutex from memory

    printf("Number of mails: %d\n", mails);
    printf("mails is equal correct: %d\n", mails == 2*BIG_NUM);
    return 0;
}
