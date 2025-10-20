#include "../includes/push_swap.h"

// Rafactor
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

int c_cust(List stack, int v)
{
    Node *temp_node;
    int cust_put_top;
    int indice;

    cust_put_top = 0;
    indice = 0;

    temp_node = stack.begin;
    while (temp_node)
    {
        if (temp_node->v == v)
            break;
        indice++;
        temp_node = temp_node->next;
    }
    if (indice <= stack.total_elements / 2)
        cust_put_top = indice;
    else
        cust_put_top = indice - stack.total_elements;
    return (cust_put_top);
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

int get_pos(List stack, int v)
{
    Node *temp_node;
    int pos;

    temp_node = stack.begin;
    pos = 0;
    while (temp_node)
    {
        if (temp_node->index == v)
            return (pos);
        pos++;
        temp_node = temp_node->next;
    }
    return (0);
}

void get_target_value(List *stack, int value_index, Node *n)
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