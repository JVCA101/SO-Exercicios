#include <semaphore.h>

// Ocorre deadlock pois os semáforos não estão sendo inicializados e porque o uso dos semáforos está incorreto,
// já que o semáforo "full" indica que o tem item no buffer e o empty indica que o buffer está vazio e o produtor espera
// que o buffer esteja cheio para produzir, enquanto que deveria esperar que esteja vazio.

sem_t empty, full;
int buffer[5], index = 0;

void produtor()
{
    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);

    for(int i = 1; i <= 10; i++)
    {
        sem_wait(&empty);
        buffer[index++] = i;
        sem_post(&full);
    }
}
