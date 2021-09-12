#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void* routine()
{
    printf("Test from thread");
}

int main()
{
    pthread_t t1;
    pthread_create(&t1, NULL, &routine, NULL);
    printf("Hello World\n");
    return 0;
}
