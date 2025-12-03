#include "../include/minitalk.h"

static char *ft_letter_to_str(char *str, const char c)
{
    int i;
    char *new_str;

    new_str = malloc((ft_strlen(str) + 2) * sizeof(char));
    if (!new_str)
        return (NULL);
    i = 0;
    while(str[i])
    {
        new_str[i] = str[i];
        i++;
    }
    new_str[i++] = c;
    new_str[i] = 0;
    free(str);
    return (new_str);
}

static void manage_signal(int signal)
{
    static int counter = 0;
    static int byte = 0;
    static char *message;
    int bit;

    if (!message)
        message = ft_strdup("");
    if (signal == SIGUSR1)
        bit = 1;
    else if (signal == SIGUSR2)
        bit = 0;
    byte = (byte << 1) | bit;
    counter++;
    if (counter == 8)
    {
        message = ft_letter_to_str(message, byte);
        if (byte == '\0')
        {
            printf("%s\n", message);
            message = NULL;
        }
        byte = 0;
        counter = 0;
    }
}
int main(void)
{
    signal(SIGUSR1, manage_signal);
    signal(SIGUSR2, manage_signal);
    printf("PID: %d\n", getpid());
    while (1)
        usleep(50);
}