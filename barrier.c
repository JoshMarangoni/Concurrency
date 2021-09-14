#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 9
#define BARRIER 3

pthread_barrier_t barrier;

void* routine(void *args) {
    printf("Waiting at the barrier.\n");
    pthread_barrier_wait(&barrier);
    printf("We passed the barrier\n");
}

int main(){
    pthread_t th[NUM_THREADS];
    int i;
    pthread_barrier_init(&barrier, NULL, BARRIER);
    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
            perror("Failed to create thread");
        }
    }
    for (i=0; i < NUM_THREADS; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    pthread_barrier_destroy(&barrier);
    return 0;
}
