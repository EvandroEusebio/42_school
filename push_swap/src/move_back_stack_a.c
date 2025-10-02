#include "../includes/push_swap.h"

void move_back(List *stack_a, List *stack_b)
{
    Node *temp_node_b;
    int target_value;
    int cust;

    if (!stack_b)
        return;
    temp_node_b = stack_b->begin;

    while (temp_node_b)
    {
        target_value = get_target_value(*stack_a, temp_node_b->v);
        cust = calculate_cust(*stack_a, target_value);
        temp_node_b = temp_node_b->next;
        move(stack_a, stack_b, cust);
        printf("New StacK A-------------------------------\n");
        show(*stack_a);
    }
}

void move(List *stack_a, List *stack_b, int cust_a)
{
    while (cust_a < 0)
    {
        reverse_rotate(stack_a, 'a');
        cust_a++;
    }
    while (cust_a > 0)
    {
        rotate(stack_a, 'a');
        cust_a--;
    }
    push_A(stack_a, stack_b);
}

int get_target_value(List stack, int value)
{
    Node *tempo_node;
    int target;

    target = INT_MAX;
    tempo_node = stack.begin;
    while (tempo_node)
    {
        if (value < tempo_node->v && tempo_node->v < target)
            target = tempo_node->v;
        tempo_node = tempo_node->next;
    }
    if (target == INT_MAX)
        return (find_min_value(stack));
    return (target);
}