#include "../includes/push_swap.h"


void set_cust(node_stack **stack_a, node_stack **stack_b)
{
    node_stack *temp_b;
    node_stack *temp_a;
    int size_a;
    int size_b;

    temp_b = *stack_b;
    temp_a = *stack_a;
    size_a = get_size(temp_a);
    size_b = get_size(temp_b);
    while (temp_b)
    {
        temp_b->cust_b = temp_b->position;
        if (temp_b->position > size_b / 2)
            temp_b->cust_b = (size_b - temp_b->position) * -1;
        temp_b->cust_a = temp_b->target_pos;
        if (temp_b->target_pos > size_a / 2)
            temp_b->cust_a = (size_a - temp_b->target_pos) * -1;
        temp_b = temp_b->next;
    }
}