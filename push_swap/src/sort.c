#include "../includes/push_swap.h"

// sorted for list with tree elements
void sorted_tree_elements(List *stack)
{
    int minor_value;
    int max_value;

    minor_value = find_min_value(*stack);
    max_value = find_max_value(*stack);
    if (minor_value == stack->begin->v && max_value == stack->begin->next->v)
    {
        swap_A(stack);
        rotate(stack, 'a');
    }
    else if (minor_value == stack->last->v && max_value == stack->begin->next->v)
        reverse_rotate(stack, 'a');
    else if (max_value == stack->last->v && minor_value == stack->begin->next->v)
        swap_A(stack);
    else
        rotate(stack, 'a');
}

void sorted_forth_elements(List *stack_a, List *stack_b)
{
    int minor_value;
    int cust_top;
    minor_value = find_min_value(*stack_a);

    // calculate cust for alloc minor in the top stack
    cust_top = calculate_cust(*stack_a, minor_value);

    // operations for push minor value A to B
    operations(stack_a, stack_b, cust_top, 0);
    
    // verify if stack_A is sorted if not sorted tree Elements
    if (is_sorted(*stack_a) == 0)
        sorted_tree_elements(stack_a);
    push_A(stack_a, stack_b);
    
}
