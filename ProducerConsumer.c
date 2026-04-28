#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 3
#define NUM_ITEMS 5

// 🔹 Shared Data
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t empty;   // free slots
sem_t full;    // filled slots
pthread_mutex_t mutex;

// 🔹 Producer
void* producer(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = id * 100 + i;

        sem_wait(&empty);               // wait if FULL
        pthread_mutex_lock(&mutex);     // enter critical section

        buffer[in] = item;
        printf("[Producer %d] Produced item %d at slot %d\n", id, item, in);

        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);   // exit critical section
        sem_post(&full);                // signal item available

        sleep(1);
    }

    printf("[Producer %d] Done.\n", id);
    return NULL;
}

// 🔹 Consumer
void* consumer(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < NUM_ITEMS; i++) {

        sem_wait(&full);                // wait if EMPTY
        pthread_mutex_lock(&mutex);     // enter critical section

        int item = buffer[out];
        printf("[Consumer %d] Consumed item %d from slot %d\n", id, item, out);

        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);   // exit critical section
        sem_post(&empty);               // signal free slot

        sleep(2);
    }

    printf("[Consumer %d] Done.\n", id);
    return NULL;
}

// 🔹 Main
int main() {

    pthread_t prod[NUM_PRODUCERS];
    pthread_t cons[NUM_CONSUMERS];

    int prod_ids[NUM_PRODUCERS];
    int cons_ids[NUM_CONSUMERS];

    // Initialize
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producers
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        prod_ids[i] = i + 1;
        pthread_create(&prod[i], NULL, producer, &prod_ids[i]);
    }

    // Create consumers
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        cons_ids[i] = i + 1;
        pthread_create(&cons[i], NULL, consumer, &cons_ids[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_PRODUCERS; i++)
        pthread_join(prod[i], NULL);

    for (int i = 0; i < NUM_CONSUMERS; i++)
        pthread_join(cons[i], NULL);

    // Cleanup
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    printf("All done. No race conditions!\n");

    return 0;
}