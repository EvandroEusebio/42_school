#include "../includes/push_swap.h"

// sorted for list with tree elements
void sorted_tree_elements(List *stack)
{
    int a = stack->begin->v;
    int b = stack->begin->next->v;
    int c = stack->last->v;

    if (a > b && b < c && a < c)
        swap_A(stack); // caso 1
    else if (a > b && b > c)
    {
        swap_A(stack); // caso 2
        reverse_rotate(stack, 'a');
    }
    else if (a > b && b < c && a > c)
        rotate(stack, 'a'); // caso 3
    else if (a < b && b > c && a < c)
    {
        swap_A(stack); // caso 4
        rotate(stack, 'a');
    }
    else if (a < b && b > c && a > c)
        reverse_rotate(stack, 'a'); // caso 5
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
