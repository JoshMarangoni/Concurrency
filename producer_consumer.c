#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 8
#define BUF_SIZE 10

int buffer[BUF_SIZE];
int count = 0;

pthread_mutex_t mutex;

sem_t semEmpty, semFull;

void* producer() {
    while(1) {
        sem_wait(&semEmpty);
        pthread_mutex_lock(&mutex);
        buffer[count++] = rand() % 100;
        pthread_mutex_unlock(&mutex);
        sem_post(&semFull);
    }
}

void *consumer() {
    while(1) {
        sem_wait(&semFull);
        pthread_mutex_lock(&mutex);
        int y = buffer[--count];
        printf("Got: %d\n", y);
        pthread_mutex_unlock(&mutex);
        sem_post(&semEmpty);
        sleep(1);
    }
}

int main(){
    pthread_t th[2];

    sem_init(&semEmpty, 0, BUF_SIZE);
    sem_init(&semFull, 0, 0);

    pthread_mutex_init(&mutex, NULL);

    for (int i=0; i < NUM_THREADS; i++) {
        if (i == 0) {
            if (pthread_create(&th[i], NULL, &producer, NULL) != 0) {
                perror("Failed to create thread\n");
            }
        } else {
            if (pthread_create(&th[i], NULL, &consumer, NULL) != 0) {
                perror("Failed to create thread\n");
            }
        }   
    }

    for (int i=0; i < NUM_THREADS; i++) {
        if (pthread_join(th[i], NULL) !=  0) {
            perror("Failed to join thread\n");
        }
    }

    pthread_mutex_destroy(&mutex);

    sem_destroy(&semEmpty);
    sem_destroy(&semFull);

    return 0;
}
