#include <semaphore.h>
#include <errno.h>

sem_t clientes = {0}, barbeiro = {0}, cadeiras_livres = {5};

void cliente()
{
    if(sem_trywait(&cadeiras_livres) != EAGAIN)
    {
        sem_post(&clientes);
        sem_wait(&barbeiro);
    }
}

void barbeiro()
{
    while(1)
    {
        sem_wait(&clientes);
        sem_post(&cadeiras_livres);
        sem_post(&barbeiro);
    }
}
