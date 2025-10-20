#include "../includes/push_swap.h"

void to_stack_b(List *stack_a, List *stack_b)
{
    int i;
    int total_push;
    int total_elements;
    i = 0;

    total_push = 0;
    total_elements = stack_a->total_elements;
    while (total_elements > 6 && i < total_elements && total_push < total_elements / 2)
    {
        if (stack_a->begin->index < total_elements / 2)
        {
            push_B(stack_a, stack_b);
            total_push++;
        }
        else
            rotate(stack_a, 'a');
        i++;
    }
    while (stack_a->total_elements - total_push > 3)
    {
        push_B(stack_a, stack_b);
        total_push++;
    }
}

void push_swap(List *stack_a, List *stack_b)
{
    if (is_sorted(*stack_a) == 1)
        return;
    if (stack_a->total_elements == 2)
    {
        swap_A(stack_a);
        return;
    }
    if (stack_a->total_elements == 3)
    {
        sorted_tree_elements(stack_a);
        return;
    }
    to_stack_b(stack_a, stack_b);
    if (is_sorted(*stack_a) == 0)
        sorted_tree_elements(stack_a);
    move_back(stack_a, stack_b);
}

void operations(List *stack_a, List *stack_b, int cust_a, int cust_b)
{
    while (cust_a < 0 && cust_b < 0)
    {
        reverse_rotate_r(stack_a, stack_b);
        cust_a++;
        cust_b++;
    }
    while (cust_a > 0 && cust_b > 0)
    {
        rotate_r(stack_a, stack_b);
        cust_a--;
        cust_b--;
    }
    while (cust_a < 0)
    {
        reverse_rotate(stack_a, 'a');
        cust_a++;
    }
    while (cust_b < 0)
    {
        reverse_rotate(stack_b, 'b');
        cust_b++;
    }
    while (cust_a > 0)
    {
        rotate(stack_a, 'a');
        cust_a--;
    }
    while (cust_b > 0)
    {
        rotate(stack_b, 'b');
        cust_b--;
    }
    push_B(stack_a, stack_b);
}
