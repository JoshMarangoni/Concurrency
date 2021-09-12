/*
 * Demonstrates the effects of race conditions. Mathematically speaking, mails
 * should be 2*BIG_NUM, however due to race conditions it is not. Race conditions
 * occur when both threads read the same value for the global variable, but one 
 * of the threads lags the other in speed and then writes down the smaller value to the
 * global variable. This results in the global variable being smaller than it
 * should be when both threads finish.
*/


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

# define BIG_NUM 1000000000

int mails = 0;

void *routine()
{
    for (int i=0; i < BIG_NUM; i++) {
        mails++;
        // Operations
        // 1. read mails
        // 2. increment
        // 3. write mails
    }
}

int main()
{
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, &routine, NULL) !=0) return 1;
    if (pthread_create(&t2, NULL, &routine, NULL) !=0) return 2;
    if (pthread_join(t1, NULL) != 0) return 3;
    if (pthread_join(t2, NULL) != 0) return 4;
    printf("Number of mails: %d\n", mails);
    printf("mails is equal correct: %d\n", mails == 2*BIG_NUM);
    return 0;
}
