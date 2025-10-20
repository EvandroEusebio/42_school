// auxiliary funtions
#include "../includes/push_swap.h"

int max_value(int a, int b)
{
    if (a > b)
        return (a);
    return (b);
}

void inicialize(List *list)
{
    list->begin = NULL;
    list->last = NULL;
    list->total_elements = 0;
}

void show(List list)
{
    Node *node;

    node = list.begin;
    while (node != NULL)
    {
        printf("%d\n", node->v);
        node = node->next;
    }
}

void free_stack(List *list)
{
    Node *temp_node;

    temp_node = list->begin;
    while (temp_node != NULL)
    {
        temp_node = temp_node->next;
        free(list->begin);
        list->begin = temp_node;
    }
    list->begin = NULL;
    list->last = NULL;
}

void show_error()
{
    printf("ERROR\n");
    exit(0);
}

void show_error_and_free(List **stack)
{
    printf("ERROR\n");
    free_stack(*stack);
    exit(0);
}

int ft_isdigit(int c)
{
    if (c >= 48 && c <= 57)
        return (2058);
    return (0);
}

int ft_atoi(char *str, List **stack)
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
    while (ft_isdigit(*str) != 0 && *str)
        value = (value * 10) + (*(str++) - '0');
    if (ft_isdigit(*str) == 0 && *str != '\0')
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

int is_sorted(List stack)
{
    Node *node;

    if (!stack.begin)
    {
        printf("Empty Stack or only value!\n");
        return (0);
    }
    node = stack.begin;
    while (node->next)
    {
        if (node->v > node->next->v)
        {
            //printf("Stack not sorted!\n");
            return (0);
        }
        node = node->next;
    }
    printf("Stack sorted!\n");
    return (1);
}
