#include "../includes/push_swap.h"


void move_back(List *stack_a, List *stack_b)
{

    if (!stack_b || !stack_a)
        return;

    while (stack_b->total_elements > 0)
    {
        set_cust(stack_a, stack_b);
        move_cheap_v(stack_a, stack_b);
    }
    put_min_top(stack_a);
}


void move(List *stack_a, List *stack_b, Node *n)
{

    while (n->cust_a > 0 && n->cust_b > 0)
    {
        rotate_r(stack_a, stack_b);
        n->cust_a--;
        n->cust_b--;
    }
    while (n->cust_a < 0 && n->cust_b < 0)
    {
        reverse_rotate_r(stack_a, stack_b);
        n->cust_a++;
        n->cust_b++;
    }
    while (n->cust_a > 0)
        rotate(stack_a, 'a'), n->cust_a--;
    while (n->cust_a < 0)
        reverse_rotate(stack_a, 'a'), n->cust_a++;
    while (n->cust_b > 0)
        rotate(stack_b, 'b'), n->cust_b--;
    while (n->cust_b < 0)
        reverse_rotate(stack_b, 'b'), n->cust_b++;

    push_A(stack_a, stack_b);
    set_pos(stack_a);
    set_pos(stack_b);
}



void get_target_pos(List *stack, int value_index, Node *n)
{
    Node *tempo_node = stack->begin;
    int target = INT_MAX;
    int target_pos = -1;

    while (tempo_node)
    {
        int idx = tempo_node->index;
        if (value_index < idx && idx < target)
        {
            target = idx;
            target_pos = tempo_node->pos;
        }
        tempo_node = tempo_node->next;
    }
    if (target == INT_MAX)
    {
        int min_index = find_min_index(*stack);
        target_pos = get_pos(*stack, min_index);
    }
    n->target_pos = target_pos;
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