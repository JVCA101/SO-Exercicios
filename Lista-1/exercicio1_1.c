#include <stdio.h>
#include <unistd.h>    // fork(), getpid()
#include <sys/types.h> // pid_t
#include <sys/wait.h>  // wait()

#define NUM_CHILDREN 3

int main(int argc, char const *argv[])
{
    // Processo pai
    pid_t father_pid = getpid();

    // Cria 3 processos filhos
    pid_t children_pid[NUM_CHILDREN];
    for(size_t i = 0; i < NUM_CHILDREN; i++)
    {
        if((children_pid[i] = fork()) < 0)
        {
            perror("fork");
            return 1;
        }

        if(children_pid[i] == 0)
        {
            printf("Processo filho (PID: %d), PID do pai: %d\n", getpid(), father_pid);
            return 0;
        }
    }

    // Wait for all child processes to finish
    for(size_t i = 0; i < NUM_CHILDREN; i++)
        wait(NULL);
    
    printf("Processo pai finalizado.\n");

    return 0;
}
