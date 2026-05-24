#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define N 3 // Number of philosophers

sem_t chopstick[N];

void *philosopher(void *num) {
    int id = *(int *)num;

    printf("Philosopher %d is thinking...\n", id);
    sem_wait(&chopstick[id]);
    sem_wait(&chopstick[(id + 1) % N]);

    printf("Philosopher %d is eating...\n", id);
    sleep(2);

    sem_post(&chopstick[id]);
    sem_post(&chopstick[(id + 1) % N]);

    printf("Philosopher %d finished eating and is thinking again...\n", id);
    return NULL;
}

int main() {
    pthread_t tid[N];
    int i, ids[N];

    for (i = 0; i < N; i++) {
        sem_init(&chopstick[i], 0, 1);
        ids[i] = i;
    }

    for (i = 0; i < N; i++) {
        pthread_create(&tid[i], NULL, philosopher, &ids[i]);
    }

    for (i = 0; i < N; i++) {
        pthread_join(tid[i], NULL);
    }

    return 0;
}

