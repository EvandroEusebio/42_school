#include "../include/minitalk.h"

static void tratar_sinal(int sinal)
{
    if (sinal == SIGUSR1)
        printf("Recebi o bit 1!\n");
    else if (sinal == SIGUSR2)
        printf("Recebi o bit 0!\n");
}
int main()
{
    int pid = getpid();
    signal(SIGUSR1, tratar_sinal);
    signal(SIGUSR2, tratar_sinal);
    printf("PID: %d\n", pid);
    while (1)
        pause();
    return (0);
}