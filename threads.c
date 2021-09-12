#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void* routine()
{
    printf("Test from thread\n");
}

int main()
{
    pthread_t t1;
    pthread_create(&t1, NULL, &routine, NULL);
    pthread_join(t1, NULL);
    printf("Hello World\n");
    return 0;
}
