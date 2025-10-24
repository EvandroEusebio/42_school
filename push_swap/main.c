#include "includes/push_swap.h"

int main(int n_args, char **args)
{
    node_stack *stack_a;
    node_stack *stack_b;
    stack_a = NULL;
    stack_b = NULL;
    if (n_args < 2)
        return (0);
    parse_args(&stack_a, n_args, args);
    add_index(stack_a, get_size(stack_a));

    push_swap(&stack_a, &stack_b);

    free_stack(&stack_a);
    free_stack(&stack_b);
    return (n_args);
}