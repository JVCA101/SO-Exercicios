#include <pthread.h>
#include <stdio.h>

// Os 2 erros de sincronização são:
// 1. Ambas threads estão acessando o mesmo endereço de memória sem exclusão mútua, ou seja, podem reescrever algo que a outra thread escreveu
// 2. Após a criação das threads, elas não se juntam novamente, o que pode levar ao término de programa antes do término das threads

int counter = 0;
pthread_mutex_t mutex;

void *increment(void *arg)
{
    for(int i = 0; i < 1000; i++)
    {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_mutex_init(&mutex, NULL);
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Counter: %d\n", counter);
    pthread_mutex_destroy(&mutex);
    return 0;
}