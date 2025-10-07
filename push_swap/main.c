#include "includes/push_swap.h"

int main(int n_args, char **args)
{
    List stack_A;
    List stack_B;
    inicialize(&stack_A);
    inicialize(&stack_B);
    if (n_args > 1)
        parsing_stack(&stack_A, args);
    else
        show_error();

    push_swap(&stack_A, &stack_B);

    printf("\n\n\nEND----------------------->\n");
    printf("Stack A ->\n");
    show(stack_A);
    printf("Stack B ->\n");
    show(stack_B);

    free_stack(&stack_A);
    free_stack(&stack_B);
    return (n_args);
}