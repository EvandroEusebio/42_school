#include "../includes/push_swap.h"

void push_swap(List *stack_a, List *stack_b)
{
    if (is_sorted(*stack_a) == 1)
        return;
    if (stack_a->total_elements == 2)
    {
        swap_A(stack_a);
        return;
    }
    else if (stack_a->total_elements == 3)
    {
        sorted_tree_elements(stack_a);
        return;
    }
    else if (stack_a->total_elements == 4)
    {
        sorted_forth_elements(stack_a, stack_b);
        return;
    }
    push_B(stack_a, stack_b);
    push_B(stack_a, stack_b);
    while (stack_a->total_elements > 3)
        cust_checker(stack_a, stack_b);
    if (is_sorted(*stack_a) == 0)
        sorted_tree_elements(stack_a);
    move_back(stack_a, stack_b);
}

// aux operation funtion
void operations(List *stack_a, List *stack_b, int cust_a, int cust_b)
{
    // for same signal
    while (cust_a < 0 && cust_b < 0)
    {
        reverse_rotate_r(stack_a, stack_b);
        cust_a++;
        cust_b++;
    }
    while (cust_a > 0 && cust_b > 0)
    {
        rotate_r(stack_a, stack_b);
        cust_a--;
        cust_b--;
    }

    // for differ signal
    while (cust_a < 0)
    {
        reverse_rotate(stack_a, 'a');
        cust_a++;
    }
    while (cust_b < 0)
    {
        reverse_rotate(stack_b, 'b');
        cust_b++;
    }
    while (cust_a > 0)
    {
        rotate(stack_a, 'a');
        cust_a--;
    }
    while (cust_b > 0)
    {
        rotate(stack_b, 'b');
        cust_b--;
    }
    push_B(stack_a, stack_b);
}

void cust_checker(List *stack_A, List *stack_B)
{
    int cust_a, cust_b;
    int minor_cust;
    int cust_a_choosed, cust_b_choosed;
    int total_cust;
    int initialized = 0;
    Node *temp_node = stack_A->begin;

    while (temp_node)
    {
        cust_a = calculate_cust(*stack_A, temp_node->v);
        cust_b = calculate_cust_b(*stack_B, temp_node->v);

        if ((cust_a < 0 && cust_b < 0) || (cust_a > 0 && cust_b > 0))
            total_cust = absolute_value(max_value(cust_a, cust_b));
        else
            total_cust = absolute_value(cust_a) + absolute_value(cust_b);

        if (!initialized || total_cust < minor_cust)
        {
            minor_cust = total_cust;
            cust_a_choosed = cust_a;
            cust_b_choosed = cust_b;
            initialized = 1;
        }
        temp_node = temp_node->next;
    }

    // Executa as operações para mover o melhor elemento
    operations(stack_A, stack_B, cust_a_choosed, cust_b_choosed);
}