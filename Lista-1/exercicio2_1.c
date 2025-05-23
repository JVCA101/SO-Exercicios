#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 10

int counter = 0;
pthread_mutex_t mutex;

void* thread_main()
{
    pthread_mutex_lock(&mutex);
    
    counter += 1000;

    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);

    for(size_t i = 0; i < NUM_THREADS; i++)
        if(pthread_create(&threads[i], NULL, &thread_main, NULL) != 0)
            return i+1;
    
    for(size_t i = 0; i < NUM_THREADS; i++)
        if(pthread_join(threads[i], NULL) != 0)
            return i+1;

    pthread_mutex_destroy(&mutex);
    printf("CONTADOR: %d\n", counter);
    return 0;
}
