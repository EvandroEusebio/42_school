#include "../includes/push_swap.h"

int get_target_position(node_stack **stack_a, int index, int max_index, int target_pos)
{
    node_stack *temp_stack_a;

    temp_stack_a = *stack_a;
    while (temp_stack_a)
    {
        if (temp_stack_a->index > index && temp_stack_a->index < max_index)
        {
            max_index = temp_stack_a->index;
            target_pos = temp_stack_a->position;
        }
        temp_stack_a = temp_stack_a->next;
    }
    if (max_index != INT_MAX)
        return (target_pos);
    temp_stack_a = *stack_a;
    while (temp_stack_a)
    {
        if (temp_stack_a->index < max_index)
        {
            max_index = temp_stack_a->index;
            target_pos = temp_stack_a->position;
        }
        temp_stack_a = temp_stack_a->next;
    }
    return (target_pos);
}

void get_stack_positions(node_stack **stack)
{
    node_stack *temp;
    int position;

    temp = *stack;
    position = 0;
    while (temp)
    {
        temp->position = position;
        temp = temp->next;
        position++;
    }
}

void put_target_pos(node_stack **stack_a, node_stack **stack_b)
{
    node_stack *b;
    int target_pos;

    b = *stack_b;
    get_stack_positions(stack_a);
    get_stack_positions(stack_b);
    target_pos = 0;
    while (b)
    {
        target_pos = get_target_position(stack_a, b->index, INT_MAX, target_pos);
        b->target_pos = target_pos;
        b = b->next;
    }
}
