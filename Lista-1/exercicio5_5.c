#include <semaphore.h>
#include <errno.h>

// ocorre deadlock pois os filósofos pegam um garfo e não soltam nem conseguem pegar o outro garfo, 
// já que outro filósofo já o pegou

sem_t garfo[5];
sem_t mutex;

void filosofo(int id)
{
    while(1)
    {
        sem_wait(&mutex);

        // Tenta pegar o primeiro garfo
        if(sem_trywait(&garfo[id]) == EAGAIN)
        {
            sem_post(&mutex);
            continue;
        }

        // Tenta pegar o segundo garfo
        if(sem_trywait(&garfo[(id+1)%5]) == EAGAIN)
        {
            sem_post(&garfo[id]);
            sem_post(&mutex);
            continue;
        }

        sem_post(&mutex);
        // Come...
        sem_post(&garfo[id]);
        sem_post(&garfo[(id+1)%5]);
    }
}
