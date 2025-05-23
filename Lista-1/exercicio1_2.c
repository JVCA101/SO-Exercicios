#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

void* thread_main()
{
    printf("Thread ID: %lu\n", pthread_self());
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t threads[NUM_THREADS];

    for(size_t i = 0; i < NUM_THREADS; i++)
        if(pthread_create(&threads[i], NULL, &thread_main, NULL) != 0)
            return i+1;

    for(size_t i = 0; i < NUM_THREADS; i++)
        if(pthread_join(threads[i], NULL) != 0)
            return i+1;
    
    return 0;
}
