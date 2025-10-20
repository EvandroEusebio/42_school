#include "includes/push_swap.h"

void showPos(List list)
{
    Node *node;

    node = list.begin;
    while (node != NULL)
    {
        printf("%d\n", node->pos);
        node = node->next;
    }
}

void showIndex(List list)
{
    Node *node;

    node = list.begin;
    while (node != NULL)
    {
        printf("%d\n", node->index);
        node = node->next;
    }
}

void showTarget(List list)
{
    Node *node;

    node = list.begin;
    while (node != NULL)
    {
        printf("%d\n", node->target_pos);
        node = node->next;
    }
}

// void showTotal(List list)
// {
//     Node *node;

//     node = list.begin;
//     while (node != NULL)
//     {
//         printf("%d\n", node->total_cust);
//         node = node->next;
//     }
// }

void get_cust_top(int size, Node *n)
{
    if (n->pos <= size / 2)
        n->cust_b = n->pos;
    else
        n->cust_b = (size - n->pos) * -1;
}

void get_cust_top_target(List stack_a, Node *n)
{
    if (n->target_pos <= stack_a.total_elements / 2)
        n->cust_a = n->target_pos;
    else
        n->cust_a = (stack_a.total_elements - n->target_pos) * -1;
}

void set_total_cust(Node *n)
{
    if ((n->cust_a < 0 && n->cust_b < 0) || (n->cust_a > 0 && n->cust_b > 0))
        n->total_cust = (absolute_value(max_value(n->cust_a, n->cust_b)));
    else
        n->total_cust = absolute_value(n->cust_a) + absolute_value(n->cust_b);
}

void set_cust(List *stack_a, List *stack_b)
{
    Node *temp_node_b;

    temp_node_b = stack_b->begin;
    while (temp_node_b)
    {
        get_cust_top(stack_b->total_elements, temp_node_b);
        get_target_value(stack_a, temp_node_b->index, temp_node_b);
        get_cust_top_target(*stack_a, temp_node_b);
        set_total_cust(temp_node_b);
        temp_node_b = temp_node_b->next;
    }
}

void move_cheap_v(List *stack_a, List *stack_b)
{
    Node *temp_node_b;
    Node *cheap_node;
    int min_total_cust;

    temp_node_b = stack_b->begin;
    min_total_cust = temp_node_b->total_cust;
    cheap_node = temp_node_b;
    while (temp_node_b)
    {
        if (temp_node_b->total_cust < min_total_cust)
        {
            cheap_node = temp_node_b;
            min_total_cust = temp_node_b->total_cust;
        }
        temp_node_b = temp_node_b->next;
    }
    move(stack_a, stack_b, cheap_node);
}

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