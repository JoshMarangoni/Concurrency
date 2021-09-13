#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int primes[10] = {2, 3, 5, 7, 11 ,13, 17, 19, 23, 29};

void* routine(void *arg) {
    sleep(1);
    int index = *(int*)arg;
    int sum = 0;
    for(int j=0; j < 5; j++) {
        sum += primes[index + j];
    }
    printf("Local sum: %d\n", sum);
    *(int*)arg = sum;
    return arg;
}

int main(){
    pthread_t th[2];
    int i;
    for (i=0; i  < 2; i++) {
        int *a = malloc(sizeof(int));
        *a = i * 5;
        if (pthread_create(&th[i], NULL, &routine, a) !=0) {
            perror("Failed to create thread");
        }
    }
    int globalSum = 0;
    for (i=0; i < 2; i++) {
        int *res;
        if (pthread_join(th[i], (void**)&res) != 0) {
            perror("Failed to join thread");
        }
        globalSum += *res;
        free(res);
    }
    printf("Global sum: %d\n", globalSum);
    return 0;
}
