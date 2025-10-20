// funtions for order
#include "../includes/push_swap.h"

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

