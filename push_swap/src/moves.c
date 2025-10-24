
#include "../includes/push_swap.h"

static void reverse_both(node_stack **sa, node_stack **sb, int *mv_a, int *mv_b)
{
    while (*mv_a < 0 && *mv_b < 0)
    {
        (*mv_a)++;
        (*mv_b)++;
        rotate_move(sa, sb, "rrr");
    }
}

static void rotate_both(node_stack **sa, node_stack **sb, int *mv_a, int *mv_b)
{
    while (*mv_a > 0 && *mv_b > 0)
    {
        (*mv_a)--;
        (*mv_b)--;
        rotate_move(sa, sb, "rr");
    }
}

static void rotate_a(node_stack **sa, int *mv_a)
{
    while (*mv_a)
    {
        if (*mv_a > 0)
        {
            rotate_move(sa, NULL, "ra");
            (*mv_a)--;
        }
        else if (*mv_a < 0)
        {
            rotate_move(sa, NULL, "rra");
            (*mv_a)++;
        }
    }
}

static void rotate_b(node_stack **sb, int *mv_b)
{
    while (*mv_b)
    {
        if (*mv_b > 0)
        {
            rotate_move(NULL, sb, "rb");
            (*mv_b)--;
        }
        else if (*mv_b < 0)
        {
            rotate_move(NULL, sb, "rrb");
            (*mv_b)++;
        }
    }
}

void move_best_cust(node_stack **sa, node_stack **sb)
{
    node_stack *b;
    int less_moves;
    int mv_a;
    int mv_b;

    b = *sb;
    less_moves = INT_MAX;
    while (b)
    {
        if (absolute_value(b->cust_a) + absolute_value(b->cust_b) < absolute_value(less_moves))
        {
            less_moves = absolute_value(b->cust_a) + absolute_value(b->cust_b);
            mv_a = b->cust_a;
            mv_b = b->cust_b;
        }
        b = b->next;
    }
    if (mv_a < 0 && mv_b < 0)
        reverse_both(sa, sb, &mv_a, &mv_b);
    else if (mv_a > 0 && mv_b > 0)
        rotate_both(sa, sb, &mv_a, &mv_b);
    rotate_a(sa, &mv_a);
    rotate_b(sb, &mv_b);
    pa(sa, sb);
}
