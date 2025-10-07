#include "../includes/push_swap.h"
// funtions for operations

void swap_A(List *stack_A)
{
    int temp;
    // perform the same action
    if (stack_A->begin == NULL)
    {
        printf("Stack_A is empty!\n");
        return;
    }
    else if (stack_A->total_elements == 1)
    {
        printf("can not to perform this action (SA)\n");
        return;
    }
    temp = stack_A->begin->v;
    stack_A->begin->v = stack_A->begin->next->v;
    stack_A->begin->next->v = temp;
    printf("sa\n");
}

void swap_B(List *stack_B)
{
    int temp;
    // perform the same action
    if (stack_B->begin == NULL)
    {
        printf("Stack_A is empty!\n");
        return;
    }
    else if (stack_B->total_elements == 1)
    {
        printf("can not to perform this action (SA)\n");
        return;
    }
    temp = stack_B->begin->v;
    stack_B->begin->v = stack_B->begin->next->v;
    stack_B->begin->next->v = temp;
    printf("sb\n");
}

void swap_A_B(List *stack_A, List *stack_B)
{
    // perform the same action
    if (stack_B->begin == NULL || stack_A->begin == NULL)
    {
        printf("Stack_A or B is empty!\n");
        return;
    }
    else if (stack_B->total_elements == 1 || stack_A->total_elements == 1)
    {
        printf("can not to perform this action (SA) with one Element \n");
        return;
    }
    swap_A(stack_A);
    swap_B(stack_B);
    printf("ss\n");
}

void push_B(List *stack_A, List *stack_B)
{
    Node *temp_node;
    // perform the same action
    if (stack_A->begin == NULL)
    {
        printf("Stack_A is empty!\n");
        return;
    }
    insert_start(&stack_B, stack_A->begin->v);
    temp_node = stack_A->begin->next;
    free(stack_A->begin);
    stack_A->begin = NULL;
    stack_A->total_elements--;
    stack_A->begin = temp_node;
    if (stack_A->begin != NULL)
        stack_A->begin->prev = NULL;
    else
        stack_A->last = NULL;
    printf("pb\n");
}

void push_A(List *stack_A, List *stack_B)
{
    Node *temp_node;
    // perform the same action
    if (stack_B->begin == NULL)
    {
        printf("Stack_B is empty!\n");
        return;
    }
    insert_start(&stack_A, stack_B->begin->v);
    temp_node = stack_B->begin->next;
    free(stack_B->begin);
    stack_B->begin = NULL;
    stack_B->total_elements--;
    stack_B->begin = temp_node;
    if (stack_B->begin != NULL)
        stack_B->begin->prev = NULL;
    else
        stack_B->last = NULL;
    printf("pa\n");
}

// r
void rotate(List *stack_A, char type_stack)
{
    Node *temp_node_head;
    Node *temp_node_last;

    if (stack_A->total_elements <= 1)
    {
        printf("Stack_A Empty!\n");
        return;
    }
    temp_node_head = stack_A->begin;
    temp_node_last = stack_A->last;

    // swap first with second
    stack_A->begin = stack_A->begin->next;
    stack_A->begin->prev = NULL;
    // swap old first for last
    stack_A->last = temp_node_head;
    stack_A->last->next = NULL;
    stack_A->last->prev = temp_node_last;
    temp_node_last->next = temp_node_head;
    if (type_stack)
        printf("r%c\n", type_stack);
}

// r->dupla
void rotate_r(List *stack_A, List *stack_B)
{
    rotate(stack_A, 0);
    rotate(stack_B, 0);
    printf("rr\n");
}

// rr
void reverse_rotate(List *stack, char type_stack)
{
    Node *temp_node_head;
    Node *temp_node_last;

    if (stack->total_elements <= 1)
    {
        printf("Stack_A Empty!\n");
        return;
    }
    temp_node_head = stack->begin;
    temp_node_last = stack->last;
    // swap last with second_last
    stack->last = stack->last->prev;
    stack->last->next = NULL;
    // swap old last for old first
    stack->begin = temp_node_last;
    stack->begin->next = temp_node_head;
    stack->begin->prev = NULL;
    temp_node_head->prev = temp_node_last;
    if (type_stack)
        printf("rr%c\n", type_stack);
}

// rrr-> dupla
void reverse_rotate_r(List *stack_A, List *stack_B)
{
    reverse_rotate(stack_A, 0);
    reverse_rotate(stack_B, 0);
    printf("rrr\n");
}