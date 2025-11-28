#include "../include/minitalk.h"

void free_buffer(char **buffer)
{
    int i;

    i = 0;
    while (buffer[i])
    {
        free(buffer[i]);
        i++;
    }
    free(buffer);
}