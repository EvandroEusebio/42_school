#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stddef.h>
#include "../libft/libft.h"

typedef struct s_stack
{
    int v;
    struct s_stack *next;
    int cust_a;
    int cust_b;
    int index;
    int total_cust;
    int position;
    int target_pos;
} node_stack;

void verify_duplicate(node_stack **stack, int value);
void add_index(node_stack *stack_a, int size);
void free_stack(node_stack **stack);
int get_size(node_stack *stack);
void show_error_and_free(node_stack **stack);
void parse_args(node_stack **stack, int n_args, char **args);
int find_min_value_with_no_index(node_stack **stack);
int is_sorted(node_stack *stack);
void push_swap(node_stack **stack_a, node_stack **stack_b);
void sa(node_stack **stack_a);
void pa(node_stack **stack_a, node_stack **stack_b);
void pb(node_stack **stack_a, node_stack **stack_b);
void rotate_move(node_stack **sa, node_stack **sb, char *choice);
void sorted_three_elements(node_stack **stack);
int find_max_index(node_stack *stack);

void move_best_cust(node_stack **stack_a, node_stack **stack_b);
void set_cust(node_stack **stack_a, node_stack **stack_b);
void move_back_to_stack_a(node_stack **stack_a, node_stack **stack_b);
void put_target_pos(node_stack **stack_a, node_stack **stack_b);
int get_target_position(node_stack **stack_a, int index, int max_index, int target_pos);
void get_stack_positions(node_stack **stack);
int absolute_value(int n);
int ft_strcmp(const char *s1, const char *s2);
void ft_putstr(char *s);
void free_buffer(char **buffer);

#endif