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

// cripto message
static char *to_binary(char c)
{
    char *bytes;
    int ascii_code;
    int bit;
    int i;

    bytes = malloc(9 * sizeof(char));
    if (!bytes)
        return (NULL);
    bytes[8] = '\0';
    ascii_code = c;
    i = 7;
    while (i >= 0)
    {
        bit = (ascii_code % 2) + '0';
        bytes[i] = bit;
        ascii_code /= 2;
        i--;
    }
    return (bytes);
}

static char **cripyto_msg(char *message)
{
    char **message_bit;
    char *bits;
    int len_message;
    int i;

    len_message = ft_strlen(message);
    message_bit = malloc((len_message + 1) * sizeof(char *));
    if (!message_bit)
        return (NULL);
    message_bit[len_message] = NULL;
    i = 0;
    while (message[i])
    {
        bits = to_binary(message[i]);
        message_bit[i] = ft_strdup(bits);
        free(bits);
        i++;
    }
    return (message_bit);
}

void send_message(int pid, char **message)
{
    int i;
    int k;

    i = 0;
    while (message[i])
    {
        k = 0;
        while (message[i][k])
        {
            if (message[i][k] == '1')
                kill(pid, SIGUSR1);
            if (message[i][k] == '0')
                kill(pid, SIGUSR2);
            usleep(100000);
            k++;
        }
        i++;
    }
}

int main(int total_args, char **args)
{
    int pid;
    char **cripyto_message;
    if (!is_validate_args(total_args, args))
    {
        printf("Error, Invalid args");
        return (0);
    }
    pid = ft_atoi(args[1]);
    cripyto_message = cripyto_msg(args[2]);
    send_message(pid, cripyto_message);
    free_buffer(cripyto_message);
    return (0);
}