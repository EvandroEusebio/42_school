#include "../includes/push_swap.h"

void set_pos(List *stack)
{
    Node *temp_stack;
    int i;

    i = 0;
    temp_stack = stack->begin;
    while (temp_stack)
    {
        temp_stack->pos = i;
        i++;
        temp_stack = temp_stack->next;
    }
}

int find_min_index(List stack)
{
    Node *t = stack.begin;
    
    if (!stack.begin)
        return INT_MAX;

    int min_idx = t->index;
    while (t)
    {
        if (t->index < min_idx)
            min_idx = t->index;
        t = t->next;
    }
    return min_idx;
}

int find_max_index(List stack)
{
    int max;
    Node *temp_node;
    int initial;
    if (!stack.begin)
    {
        printf("Nenhum valor maximo!");
        exit(0);
    }
    max = 0;
    temp_node = stack.begin;
    initial = 0;
    while (temp_node)
    {
        if (initial == 0)
        {
            max = temp_node->index;
            initial++;
        }
        else if (temp_node->index > max)
            max = temp_node->index;
        temp_node = temp_node->next;
    }
    return (max);
}

int get_pos(List stack, int v)
{
    Node *temp_node;
    int pos;

    temp_node = stack.begin;
    pos = 0;
    while (temp_node)
    {
        if (temp_node->index == v)
            return (pos);
        pos++;
        temp_node = temp_node->next;
    }
    return (0);
}