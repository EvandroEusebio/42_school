#include "../includes/push_swap.h"

void sa(node_stack **stack_a)
{
    int temp;

    if (!stack_a || !*stack_a || !(*stack_a)->next)
        return;
    temp = (*stack_a)->index;
    (*stack_a)->index = (*stack_a)->next->index;
    (*stack_a)->next->index = temp;
    (*stack_a)->v = (*stack_a)->next->v;
    (*stack_a)->next->v = temp;
    ft_putstr("sa\n");
}


void pa(node_stack **stack_a, node_stack **stack_b)
{
    node_stack *node_to_move;

    if (!stack_b || !*stack_b)
        return;
    node_to_move = *stack_b;
    *stack_b = (*stack_b)->next;
    node_to_move->next = *stack_a;
    *stack_a = node_to_move;
    ft_putstr("pa\n");
}

void pb(node_stack **stack_a, node_stack **stack_b)
{
    node_stack *node_to_move;

    if (!stack_a || !*stack_a)
        return;
    node_to_move = *stack_a;
    *stack_a = (*stack_a)->next;
    node_to_move->next = *stack_b;
    *stack_b = node_to_move;
    ft_putstr("pb\n");
}



static void	reverse(node_stack **top)
{
	node_stack	*ex_top;
	node_stack	*new_bottom;
	node_stack	*ex_bottom;

	ex_bottom = *top;
	new_bottom = *top;
	ex_top = *top;
	while (ex_bottom->next)
		ex_bottom = ex_bottom->next;
	while (new_bottom->next->next)
		new_bottom = new_bottom->next;
	*top = ex_bottom;
	(*top)->next = ex_top;
	new_bottom->next = NULL;
}

static void	rotate(node_stack **top)
{
	node_stack	*ex_top;
	node_stack	*bottom;

	ex_top = *top;
	*top = (*top)->next;
	bottom = *top;
	while (bottom->next)
		bottom = bottom->next;
	ex_top->next = NULL;
	bottom->next = ex_top;
}

void	rotate_move(node_stack **sa, node_stack **sb, char *choice)
{
	if (ft_strcmp(choice, "ra") == 0)
		rotate(sa);
	else if (ft_strcmp(choice, "rb") == 0)
		rotate(sb);
	else if (ft_strcmp(choice, "rr") == 0)
	{
		rotate(sa);
		rotate(sb);
	}
	else if (ft_strcmp(choice, "rra") == 0)
		reverse(sa);
	else if (ft_strcmp(choice, "rrb") == 0)
		reverse(sb);
	else if (ft_strcmp(choice, "rrr") == 0)
	{
		reverse(sa);
		reverse(sb);
	}
	ft_putstr(choice);
	ft_putstr("\n");
}