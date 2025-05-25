#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// código original gera processos zumbis poque o pai espera que os filhos terminem dentro de 5 segundos, porém eles podem demorar mais que isso para terminar,
// por conta disso, o pai termina antes dos filhos, e eles ficam como processos zumbis.

int main()
{
    for(int i = 0; i < 3; i++)
        if(fork() == 0)
        {
            printf("Filho %d criado\n", getpid());
            return 0;
        }
    
    for(int i = 0; i < 3; i++)
        wait(NULL);
    printf("Pai finalizado\n");
    return 0;
}
