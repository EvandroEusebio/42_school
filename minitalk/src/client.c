#include "../include/minitalk.h"

static int is_validate_args(int total_args, char **args)
{
    int i;
    if (total_args != 3)
        return (0);
    i = 0;
    while (args[1][i])
    {
        if (!ft_strchr("0123456789", args[1][i]))
            return (0);
        i++;
    }
    return (1);
}


void send_message(int pid, char *message)
{
    int i;
    int k;

    i = 0;
    while (message[i])
    {
        k = -1;
        while(++k < 8)
        {
            if ((message[i] >> (7 - k)) & 1)
                kill(pid, SIGUSR1);
            else
                kill(pid, SIGUSR2);
            usleep(50);
        }
        i++;
    }
    k = 0;
    while (k++ < 8)
    {
        kill(pid, SIGUSR2);
        usleep(50);
    }
}

int main(int total_args, char **args)
{
    int pid;
    if (!is_validate_args(total_args, args))
    {
        printf("Error, Invalid args");
        return (0);
    }
    pid = ft_atoi(args[1]);
    send_message(pid, args[2]);
    return (0);
}

/*
while (message[i][k])
        {
            if (message[i][k] == '1')
                kill(pid, SIGUSR1);
            else
                kill(pid, SIGUSR2);
            usleep(50);
            k++;
        }

*/