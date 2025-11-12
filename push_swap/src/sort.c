#include "../includes/push_swap.h"

void sorted_three_elements(node_stack **stack)
{
    int max_value;

    if (is_sorted(*stack))
        return;
    max_value = find_max_index(*stack);

    if ((*stack)->index == max_value)
        rotate_move(stack, NULL, "ra");
    else if ((*stack)->next->index == max_value)
        rotate_move(stack, NULL, "rra");
    if ((*stack)->index > (*stack)->next->index)
        sa(stack);
}