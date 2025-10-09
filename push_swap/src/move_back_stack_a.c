#include "../includes/push_swap.h"

int find_position(List stack, int v)
{
    int pos;
    Node *temp_node;
    
    pos = 0;
    temp_node = stack.begin;
    while (temp_node)
    {
        if(temp_node->v == v)
            return (pos);
        pos++;
        temp_node = temp_node->next;
    }
    return (pos);
}

void put_min_top(List *stack)
{
    int min_value;
    int pos;
    int half;

    min_value = find_min_value(*stack);
    pos = find_position(*stack, min_value);
    half = stack->total_elements / 2;
    if (pos <= half)
    {
        while (stack->begin->v != min_value)
            rotate(stack, 'a');
    }
    else
    {
        while (stack->begin->v != min_value)
            reverse_rotate(stack, 'a');
    }
}

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
        target_value = get_target_value_a(*stack_a, temp_node_b->v);
        cust = calculate_cust(*stack_a, target_value);
        temp_node_b = temp_node_b->next;
        move(stack_a, stack_b, cust);
        put_min_top(stack_a);
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

int get_target_value_a(List stack, int value)
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

int get_target_value_b(List stack, int value)
{
    Node *tempo_node;
    int target;

    /* Se a lista estiver vazia cuide conforme seu caso */
    target = INT_MIN;
    tempo_node = stack.begin;
    while (tempo_node)
    {
        /* procura o maior valor que seja < value */
        if (tempo_node->v < value && tempo_node->v > target)
            target = tempo_node->v;
        tempo_node = tempo_node->next;
    }
    /* se não encontrou nenhum < value, faz wrap-around pegando o máximo */
    if (target == INT_MIN)
        return find_max_value(stack);
    return target;
}