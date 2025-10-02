// essencial funtions for manipulate stacks
#include "../includes/push_swap.h"


int insert_start(List **list, int v)
{
    Node *n;

    n = (Node *)malloc(sizeof(Node));
    if (!n)
        return (1);
    if ((*list)->begin != NULL)
        (*list)->begin->prev = n;
    n->next = (*list)->begin;
    (*list)->begin = n;
    n->v = v;
    if ((*list)->last == NULL)
        (*list)->last = n;
    (*list)->total_elements++;
    return (0);
}

int insert_end(List **list, int v)
{
    Node *n;

    if ((*list)->begin == NULL)
    {
        insert_start(list, v);
        return (0);
    }
    n = (Node *)malloc(sizeof(Node));
    if (!n)
        return (1);
    n->prev = (*list)->last;
    (*list)->last->next = n;
    (*list)->last = n;
    n->next = NULL;
    n->v = v;
    (*list)->total_elements++;
    return (0);
}

void verify_duplicate_n(List **list, int number)
{
    Node *temp_node;

    temp_node = (*list)->begin;
    while (temp_node != NULL)
    {
        if (number == temp_node->v)
        {
            printf("Duplicate value!\n");
            show_error_and_free(list);
        }
        temp_node = temp_node->next;
    }
    // printf("Nothing igual number!\n");
}

int parsing_stack(List *stack, char **args)
{
    int n;
    int i;

    i = 0;
    while (*(++args))
    {
        n = ft_atoi(*args, &stack);
        verify_duplicate_n(&stack, n);
        insert_end(&stack, n);
        i++;
    }
    return (0);
}