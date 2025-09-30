#include "../includes/push_swap.h"


void push_swap(List *stack_a, List *stack_b)
{
    if (stack_a->total_elements <= 1)
        return ;
    else if (stack_a->total_elements == 2)
    {
        swap_A(stack_a);
        return ;
    }
    else if(stack_a->total_elements == 4)
    {
        sorted_forth_elements(stack_a, stack_b);
        return ;
    }
    else if (stack_a->total_elements > 4)
    {
        push_B(stack_a, stack_b);
        push_B(stack_a, stack_b);
    }
    while (stack_a->total_elements > 3)
    {
        cust_checker(stack_a, stack_b);
        printf("Stack A ->\n");
        show(*stack_a);
        printf("Stack B ->\n");
        show(*stack_b);
    }
     is_sorted(*stack_a);
     sorted_tree_elements(stack_a);
     printf("sort Stack A ->\n");
     show(*stack_a);
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


int cust_checker(List *stack_A, List *stack_B)
{
    int cust_a;
    int cust_b;
    int initial_verification;
    int minor_cust;
    int value_choosed;
    int cust_a_choosed;
    int cust_b_choosed;
    int total_cust;
    Node *temp_node;

    temp_node = stack_A->begin;
    initial_verification = 0;
    while (temp_node)
    {
        cust_a = calculate_cust(*stack_A, temp_node->v);
        cust_b = calculate_cust_b(*stack_B, temp_node->v);
        if ((cust_a < 0 && cust_b < 0) || (cust_a > 0 && cust_b > 0))
            total_cust = (absolute_value(max_value(cust_a, cust_b))) + 1;
        else
            total_cust = absolute_value(cust_a) + absolute_value(cust_b) + 1;
        // printf("Cust A: %d\n", cust_a);
        // printf("Cust B: %d\n", cust_b);
        // printf("Total Cust: %d\n", total_cust);
        if (initial_verification == 0)
        {
            minor_cust = total_cust;
            value_choosed = temp_node->v;
            initial_verification++;
            cust_a_choosed = cust_a;
            cust_b_choosed = cust_b;
        }
        else if (total_cust < minor_cust)
        {
            minor_cust = total_cust;
            value_choosed = temp_node->v;
            cust_a_choosed = cust_a;
            cust_b_choosed = cust_b;
        }
        temp_node = temp_node->next;
    }
    // operation
    operations(stack_A, stack_B, cust_a_choosed, cust_b_choosed);
    return (value_choosed);
}