#include "../include/minitalk.h"

static void manage_signal(int signal)
{
    // char *criypted_code;
    static int counter = 0;
    static int byte = 0;
    int bit;

    if (signal == SIGUSR1)
        bit = 1;
    else if (signal == SIGUSR2)
        bit = 0;
    byte = (byte << 1) | bit;
    counter++;
    if (counter == 8)
    {
        printf("Valor inteiro: %d\n", byte);
        exit(0);
    }
}
int main(void)
{
    int pid = getpid();
    signal(SIGUSR1, manage_signal);
    signal(SIGUSR2, manage_signal);
    printf("PID: %d\n", pid);
    while (1)
        usleep(50);
}