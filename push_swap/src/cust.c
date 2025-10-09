// funtions for order
#include "../includes/push_swap.h"

int calculate_cust_b(List stack_b, int value)
{
    int max_value;
    int min_value;
    int cust;
    int pos_fit;
    int target;

    max_value = find_max_value(stack_b);
    min_value = find_min_value(stack_b);

    if (value > max_value || value < min_value)
        cust = calculate_cust(stack_b, max_value);
    else
    {
        target = get_target_value_b(stack_b, value);
        pos_fit = calculate_cust(stack_b, target);
        return (pos_fit);
    }
    return (cust);
}

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
    int index;
    int min_max;
    Node *temp_node;

    if (!stack.begin)
        return (0);
    pos = 0;
    index = 0;
    temp_node = stack.begin;
    min_max = INT_MIN;
    while (temp_node)
    {
        if (value > temp_node->v && temp_node->v > min_max)
        {
            min_max = temp_node->v;
            pos = index;
        }
        index++;
        temp_node = temp_node->next;
    }
    return (pos);
}
