#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define MAX_BUFFER_SIZE 100
int buffer[MAX_BUFFER_SIZE];
int buffer_index;
pthread_mutex_t mutex;
sem_t full_sem, empty_sem;
void *producer(void *arg) {
int i;
int num_items = *(int *) arg;
for (i = 0; i < num_items; i++) {
sem_wait(&empty_sem);
pthread_mutex_lock(&mutex);
buffer[buffer_index++] = i;
printf("Producer produced %d \n", i);
pthread_mutex_unlock(&mutex);
sem_post(&full_sem);
}
pthread_exit(NULL);
}
void *consumer(void *arg) {
int i, item;
int num_items = *(int *) arg;
for (i = 0; i < num_items; i++) {
sem_wait(&full_sem);
pthread_mutex_lock(&mutex);
item = buffer[--buffer_index];
printf("Consumer consumed %d \n", item);
pthread_mutex_unlock(&mutex);
sem_post(&empty_sem);
}
pthread_exit(NULL);
}
int main() {
int num_producers, num_consumers, num_items;
printf("Enter the number of producers:");
scanf("%d", &num_producers);
printf("Enter the number of consumers:");
scanf("%d", &num_consumers);
printf("Enter the numbers of items to produce:");
scanf("%d", &num_items);
pthread_t producers[num_producers], consumers[num_consumers];
pthread_mutex_init(&mutex, NULL);
sem_init(&full_sem, 0, 0);
sem_init(&empty_sem, 0, MAX_BUFFER_SIZE);
buffer_index = 0;
int item_count = num_items;
int i;
for (i = 0; i < num_producers; i++) {
pthread_create(&producers[i], NULL, producer, &item_count);
}
for (i = 0; i < num_consumers; i++) {
pthread_create(&consumers[i], NULL, consumer, &item_count);
}
for (i = 0; i < num_producers; i++) {
pthread_join(producers[i], NULL);
}
for (i = 0; i < num_consumers; i++) {
pthread_join(consumers[i], NULL);
}
pthread_mutex_destroy(&mutex);
sem_destroy(&full_sem);
sem_destroy(&empty_sem);
return 0;
}