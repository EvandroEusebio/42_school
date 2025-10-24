#include "../includes/push_swap.h"

void	put_min_to_top(node_stack **sa)
{
	int	size;
	int	min_position;

	size = get_size(*sa);
	min_position = find_min_value_with_no_index(sa);
	if (min_position > size / 2)
	{
		while (min_position < size)
        {
            rotate_move(sa, NULL, "rra");
            min_position++;
        }
	}
	else
	{
		while (min_position--)
			rotate_move(sa, NULL, "ra");
	}
}


void move_back_to_stack_a(node_stack **stack_a, node_stack **stack_b)
{

    while (*stack_b)
    {
        put_target_pos(stack_a, stack_b);
        set_cust(stack_a, stack_b);
        move_best_cust(stack_a, stack_b);
    }
    put_min_to_top(stack_a);
}