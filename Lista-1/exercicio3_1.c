#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE] = {0};

//! revise semaphores

sem_t empty, full;
pthread_t consumidor;
pthread_t produtor;
pthread_mutex_t mutex;


void* produtor_main()
{
    int counter = 1;
    int i = 0;
    while(1)
    {
        // sem_wait(&semaphore);
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[i] = counter;
        pthread_mutex_unlock(&mutex);
        i = (i + 1) % BUFFER_SIZE;
        counter = counter % 10 + 1;
        sem_post(&full);
        sleep(1);
    }
}

void* consumidor_main()
{
    int i = 0;
    while (1)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[i];
        buffer[i] = 0;
        pthread_mutex_unlock(&mutex);
        printf("Consumidor: %d\n", item);
        i = (i + 1) % BUFFER_SIZE;
        sem_post(&empty);
        sleep(1);
    }    
}

int main(int argc, char const *argv[])
{
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_create(&produtor, NULL, produtor_main, NULL);
    pthread_create(&consumidor, NULL, consumidor_main, NULL);

    pthread_join(produtor, NULL);
    pthread_join(consumidor, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}
