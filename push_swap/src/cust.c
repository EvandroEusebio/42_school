// funtions for order
#include "../includes/push_swap.h"

int calculate_cust_b(List stack_b, int value)
{
    int max_value;
    int min_value;
    int cust;
    int pos_fit;

    max_value = find_max_value(stack_b);
    min_value = find_min_value(stack_b);

    if (value > max_value || value < min_value)
        cust = calculate_cust(stack_b, max_value);
    else
    {
        pos_fit = pos_fit_value(stack_b, value);
        printf("Pos Fit: %d\n", pos_fit);
        return (pos_fit);
    }
    printf("Custo: %d\n", cust);
    return (cust);
}

// the calcule of the cust in A is diferent of B
int calculate_cust(List stack, int v)
{
    int pos_value;
    Node *temp_node;
    int cust;

    pos_value = 0;
    temp_node = stack.begin;
    if (!temp_node)
        return (0);
    while (temp_node->v != v && temp_node)
    {
        pos_value++;
        temp_node = temp_node->next;
    }
    cust = (stack.total_elements) - pos_value;
    if (cust >= pos_value)
        return (pos_value);
    else
        return (-cust);
}

int find_min_value(List stack)
{
    int min;
    Node *temp_node;
    int initial;
    if (!stack.begin)
    {
        printf("Nenhum valor mínimo!");
        exit(0);
    }
    min = 0;
    temp_node = stack.begin;
    initial = 0;
    while (temp_node)
    {
        if (initial == 0)
        {
            min = temp_node->v;
            initial++;
        }
        else if (temp_node->v < min)
            min = temp_node->v;
        temp_node = temp_node->next;
    }
    return (min);
}

int find_max_value(List stack)
{
    int max;
    Node *temp_node;
    int initial;
    if (!stack.begin)
    {
        printf("Nenhum valor maximo!");
        exit(0);
    }
    max = 0;
    temp_node = stack.begin;
    initial = 0;
    while (temp_node)
    {
        if (initial == 0)
        {
            max = temp_node->v;
            initial++;
        }
        else if (temp_node->v > max)
            max = temp_node->v;
        temp_node = temp_node->next;
    }
    return (max);
}

// refazer
int pos_fit_value(List stack, int value)
{
    int pos;
    Node *temp_node;

    if (!stack.begin)
        return (0);

    pos = 0;
    temp_node = stack.begin;

    while (temp_node)
    {
        if (temp_node->v > value)
        {
            return pos + 1;
        }
        temp_node = temp_node->next;
        pos++;
    }
    return (0);
}

// esta a falta o cust B
/*
int calculate_cust_B(List stack, int v_other_stack)
{
    int pos_value;
    // Node *temp_node;
    int cust;
    int max_value;

    if (!stack.begin)
        return (0);
    max_value = find_max_value(stack);
    if (v_other_stack > max_value || v_other_stack < find_min_value(stack))
        pos_value = calculate_cust(stack, max_value);
    else
        pos_value = pos_fit_value(stack, v_other_stack);
    if (pos_value <= stack.total_elements / 2)
        cust = pos_value;
    else
        cust = -(stack.total_elements - pos_value);
    return (cust);
}
    
// esta a falta o cust B
int calculate_cust_B(List stack, int v_other_stack)
{
    int pos_value;
    // Node *temp_node;
    int cust;
    int max_value;

    if (!stack.begin)
        return (0);
    max_value = find_max_value(stack);
    if (v_other_stack > max_value || v_other_stack < find_min_value(stack))
        return (calculate_cust(stack, max_value));
    pos_value = pos_fit_value(stack, v_other_stack);
    cust = (stack.total_elements) - pos_value;
    if (cust >= pos_value)
        return (pos_value);
    else
        return (-cust);
}
        */
