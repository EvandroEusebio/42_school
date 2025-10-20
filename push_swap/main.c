#include "includes/push_swap.h"

// void showPos(List list)
// {
//     Node *node;

//     node = list.begin;
//     while (node != NULL)
//     {
//         printf("%d\n", node->pos);
//         node = node->next;
//     }
// }



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
    addIndex(&stack_A);
    push_swap(&stack_A, &stack_B);

    free_stack(&stack_A);
    free_stack(&stack_B);
    return (n_args);
}