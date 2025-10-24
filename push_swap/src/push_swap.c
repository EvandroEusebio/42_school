#include "../includes/push_swap.h"


void move_to_stack_b(node_stack **stack_a, node_stack **stack_b)
{
    int size;
    int pushed;
    int i;

    size = get_size(*stack_a);
    pushed = 0;
    i = 0;
    while (size > 6 && i < size && pushed < size / 2)
    {
        if ((*stack_a)->index <= size / 2)
        {
            pb(stack_a, stack_b);
            pushed++;
        }
        else
            rotate_move(stack_a, NULL, "ra");
        i++;
    }
    while (size - pushed > 3)
    {
        pb(stack_a, stack_b);
        pushed++;
    }
}

void push_swap(node_stack **stack_a, node_stack **stack_b)
{
    if(is_sorted(*stack_a))
        return;
    if (get_size(*stack_a) == 2)
        sa(stack_a);
    if (get_size(*stack_a) == 3)
        sorted_three_elements(stack_a);
    move_to_stack_b(stack_a, stack_b);
    sorted_three_elements(stack_a);
    move_back_to_stack_a(stack_a, stack_b);
}