#include "../includes/push_swap.h"

// sorted for list with tree elements
void sorted_tree_elements(List *stack)
{
    int minor_value;
    int max_value;

    minor_value = find_min_index(*stack);
    max_value = find_max_index(*stack);
    if (minor_value == stack->begin->v && max_value == stack->begin->next->v)
    {
        swap_A(stack);
        rotate(stack, 'a');
    }
    else if (minor_value == stack->last->v && max_value == stack->begin->next->v)
        reverse_rotate(stack, 'a');
    else if (max_value == stack->last->v && minor_value == stack->begin->next->v)
        swap_A(stack);
    else if (max_value == stack->begin->v && minor_value == stack->last->v)
    {
        rotate(stack, 'a');
        swap_A(stack);
    }
    else if (max_value == stack->begin->v && minor_value == stack->begin->next->v)
        rotate(stack, 'a');
    else
        reverse_rotate(stack, 'a');
}