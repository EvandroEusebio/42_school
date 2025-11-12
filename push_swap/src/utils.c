#include "../includes/push_swap.h"

int ft_strcmp(const char *s1, const char *s2)
{
    size_t i;

    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void ft_putstr(char *s)
{
    while (*s)
    {
        write(1, &*s, 1);
        s++;
    }
}

void show_error_and_free(node_stack **stack)
{
    ft_putstr("ERROR\n");
    free_stack(stack);
    exit(2);
}

void show_error()
{
    ft_putstr("ERROR\n");
    exit(2);
}

int absolute_value(int value)
{
    if (value < 0)
        return (value * -1);
    return (value);
}

int is_digit(int c)
{
    if (c >= 48 && c <= 57)
        return (2058);
    return (0);
}

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