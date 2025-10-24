#include "../includes/push_swap.h"

int get_size(node_stack *stack)
{
    int size;
    node_stack *temp;
    temp = stack;
    size = 0;
    while (temp)
    {
        size++;
        temp = temp->next;
    }
    return size;
}

void free_stack(node_stack **stack)
{
    node_stack *temp_node;
    node_stack *current;

    if (!stack || !*stack)
        return;

    current = *stack;
    while (current != NULL)
    {
        temp_node = current->next;
        free(current);
        current = temp_node;
    }
    *stack = NULL;
}
// void show_stack(node_stack *stack)
// {
//     node_stack *temp;
//     temp = stack;
//     while (temp)
//     {
//         printf("Value: %d | Index: %d | pos: %d\n", temp->v, temp->index, temp->position);
//         temp = temp->next;
//     }
// }

void show_error_and_free(node_stack **stack)
{
    printf("ERROR\n");
    free_stack(stack);
    exit(0);
}

void show_error()
{
    printf("ERROR\n");
    exit(0);
}

int ft_atoi(const char *str, node_stack **stack)
{
    long int value;
    int signal;
    int n_int;

    signal = 1;
    value = 0;
    if (!str)
        show_error_and_free(stack);
    while ((*str == 32) || (*str >= 7 && *str <= 13))
        str++;
    if (*str == 45 || *str == 43)
    {
        if (*str == 45)
            signal = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9' && *str)
        value = (value * 10) + (*(str++) - '0');
    if ((*str < '0' || *str > '9') && *str != '\0')
        show_error_and_free(stack);
    if ((value * signal) > INT_MAX || (value * signal) < INT_MIN)
        show_error_and_free(stack);
    n_int = value * signal;
    return (n_int);
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

int find_max_index(node_stack *stack)
{
    int max_index;
    node_stack *temp;

    if (!stack)
        return (-1);

    max_index = stack->index;
    temp = stack->next;
    while (temp)
    {
        if (temp->index > max_index)
            max_index = temp->index;
        temp = temp->next;
    }
    return (max_index);
}

int ft_strcmp(const char *s1, const char *s2)
{
    size_t i;

    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_putstr(char *s)
{
	while (*s)
	{
		write(1, &*s, 1);
		s++;
	}
}