#include "../includes/push_swap.h"

int insert_end(node_stack **stack, int v, int index)
{
    node_stack *new_node;
    node_stack *temp;

    new_node = (node_stack *)malloc(sizeof(node_stack));
    if (!new_node)
        return (1);
    new_node->v = v;
    new_node->index = index;
    new_node->next = NULL;
    new_node->cust_a = -1;
    new_node->cust_b = -1;
    new_node->position = -1;
    new_node->target_pos = -1;
    if (*stack == NULL)
        *stack = new_node;
    else
    {
        temp = *stack;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new_node;
    }
    return (0);
}

void verify_duplicate(node_stack **stack, int value)
{
    node_stack *temp_node;

    temp_node = *stack;
    while (temp_node)
    {
        if (temp_node->v == value)
        {
            ft_putstr("Error\n");
            exit(2);
        }
        temp_node = temp_node->next;
    }
}

int find_min_value_with_no_index(node_stack **stack)
{
    int min_index;
    node_stack *temp;
    int min_position;

    if (!stack)
        return (-1);
    min_index = INT_MAX;
    temp = *stack;
    get_stack_positions(stack);
    min_position = temp->position;
    while (temp)
    {
        if (temp->index < min_index)
        {
            min_index = temp->index;
            min_position = temp->position;
        }
        temp = temp->next;
    }
    return (min_position);
}

void add_index(node_stack *stack_a, int size)
{
    node_stack *temp_stack;
    node_stack *max_address;
    int max_n;

    while (size--)
    {
        temp_stack = stack_a;
        max_n = INT_MIN;
        max_address = NULL;
        while (temp_stack)
        {
            if (temp_stack->v == INT_MIN && temp_stack->index == 0)
                temp_stack->index = 1;
            else if (temp_stack->v > max_n && temp_stack->index == 0)
            {
                max_n = temp_stack->v;
                max_address = temp_stack;
                temp_stack = stack_a;
            }
            else
                temp_stack = temp_stack->next;
        }
        if (max_address)
            max_address->index = size + 1;
    }
}

void parse_args(node_stack **stack, int n_args, char **args)
{
    char **numbers;
    int i;
    long value;

    if (n_args == 2)
        numbers = ft_split(args[1], ' ');
    else
        numbers = args + 1;
    i = 0;
    while (numbers[i])
    {
        value = ft_atoi(numbers[i]);
        if (value > INT_MAX || value < INT_MIN)
        {
            if (n_args == 2)
                free_buffer(numbers);
            show_error_and_free(stack);
        }
        verify_duplicate(stack, value);
        insert_end(stack, value, 0);
        i++;
    }
    if (n_args == 2)
        free_buffer(numbers);
}


