#include "../includes/push_swap.h"

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
        get_target_pos(stack_a, temp_node_b->index, temp_node_b);
        get_cust_top_target(*stack_a, temp_node_b);
        set_total_cust(temp_node_b);
        temp_node_b = temp_node_b->next;
    }
}

void put_min_top(List *stack)
{
    int min_index = find_min_index(*stack);
    int cust_top_min = get_pos(*stack, min_index);

    if (cust_top_min > stack->total_elements / 2)
        cust_top_min = (stack->total_elements - cust_top_min) * -1;

    if (cust_top_min > 0)
        while (cust_top_min--)
            rotate(stack, 'a');
    else
        while (cust_top_min++)
            reverse_rotate(stack, 'a');
}