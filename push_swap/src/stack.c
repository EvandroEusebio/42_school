#include "../includes/push_swap.h"

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

int is_sorted(node_stack *stack)
{
    node_stack *temp;

    if (!stack)
        return 1;

    temp = stack;
    while (temp->next)
    {
        if (temp->v > temp->next->v)
            return 0;
        temp = temp->next;
    }
    return 1;
}
