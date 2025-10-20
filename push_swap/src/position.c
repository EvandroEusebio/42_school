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