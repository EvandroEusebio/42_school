#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node
{
    int v;
    struct node *next;
    struct node *prev;
} Node;

typedef struct list
{
    Node *begin;
    Node *last;
    int total_elements;
} List;

void inicialize(List *list)
{
    list->begin = NULL;
    list->last = NULL;
    list->total_elements = 0;
}

int insert_start(List **list, int v)
{
    Node *n;

    n = (Node *)malloc(sizeof(Node));
    if (!n)
        return (1);
    if ((*list)->begin != NULL)
        (*list)->begin->prev = n;
    n->next = (*list)->begin;
    (*list)->begin = n;
    n->v = v;
    if ((*list)->last == NULL)
        (*list)->last = n;
    (*list)->total_elements++;
    return (0);
}

int insert_end(List **list, int v)
{
    Node *n;

    if ((*list)->begin == NULL)
    {
        insert_start(list, v);
        return (0);
    }
    n = (Node *)malloc(sizeof(Node));
    if (!n)
        return (1);
    n->prev = (*list)->last;
    (*list)->last->next = n;
    (*list)->last = n;
    n->next = NULL;
    n->v = v;
    (*list)->total_elements++;
    return (0);
}

void show(List list)
{
    Node *node;

    node = list.begin;
    while (node != NULL)
    {
        printf("%d\n", node->v);
        node = node->next;
    }
}

void free_stack(List *list)
{
    Node *temp_node;

    temp_node = list->begin;
    while (temp_node != NULL)
    {
        temp_node = temp_node->next;
        free(list->begin);
        list->begin = temp_node;
    }
    list->begin = NULL;
    list->last = NULL;
}

void show_error()
{
    printf("ERROR\n");
    exit(0);
}

void show_error_and_free(List **stack)
{
    printf("ERROR\n");
    free_stack(*stack);
    exit(0);
}

int ft_isdigit(int c)
{
    if (c >= 48 && c <= 57)
        return (2058);
    return (0);
}

int ft_atoi(char *str, List **stack)
{
    long int value;
    int signal;
    int n_int;

    signal = 1;
    value = 0;
    if (!str)
        show_error_and_free(stack);
    while ((*str == 32) || (*str >= 7 && *str <= 13))
        str++;
    if (*str == 45 || *str == 43)
    {
        if (*str == 45)
            signal = -1;
        str++;
    }
    while (ft_isdigit(*str) != 0 && *str)
        value = (value * 10) + (*(str++) - '0');
    // verify if exist character not digit
    if (ft_isdigit(*str) == 0 && *str != '\0')
        show_error_and_free(stack);
    // verify if NUMBER converted is better than INT_MAX or INT_MIN
    if ((value * signal) > INT_MAX || (value * signal) < INT_MIN)
        show_error_and_free(stack);
    n_int = value * signal;
    return (n_int);
}

void verify_duplicate_n(List **list, int number)
{
    Node *temp_node;

    temp_node = (*list)->begin;
    while (temp_node != NULL)
    {
        if (number == temp_node->v)
        {
            printf("Duplicate value!\n");
            show_error_and_free(list);
        }
        temp_node = temp_node->next;
    }
    // printf("Nothing igual number!\n");
}

int parsing_stack(List *stack, char **args)
{
    int n;
    int i;

    i = 0;
    while (*(++args))
    {
        n = ft_atoi(*args, &stack);
        verify_duplicate_n(&stack, n);
        insert_end(&stack, n);
        i++;
    }
    return (0);
}

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
    printf("Stack A\n");
    show(*stack_A);
    printf("Stack B\n");
    show(*stack_B);
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
    printf("Stack A\n");
    show(*stack_A);
    printf("Stack B\n");
    show(*stack_B);
    printf("pa\n");
}

// the rotate B funtion does the same thing create an value for controller this type
// void rotate_A(List *stack_A)
// {
//     Node *temp_node_head;
//     Node *temp_node_last;

//     if (stack_A->total_elements <= 1)
//     {
//         printf("Stack_A Empty!\n");
//         return ;
//     }
//     temp_node_head = stack_A->begin;
//     stack_A->begin = stack_A->begin->next;
//     stack_A->begin->prev = NULL;
//     temp_node_last = stack_A->last;
//     stack_A->last = temp_node_head;
//     temp_node_last->next = stack_A->last;
//     stack_A->last->prev = temp_node_last;
//     stack_A->last->next = NULL;
//     printf("ra\n");
// }

void rotate_A(List *stack_A)
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

    printf("ra\n");
}

void reverse_rotate_A(List *stack_A)
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
    // swap last with second_last
    stack_A->last = stack_A->last->prev;
    stack_A->last->next = NULL;
    // swap old last for old first
    stack_A->begin = temp_node_last;
    stack_A->begin->next = temp_node_head;
    stack_A->begin->prev = NULL;
    temp_node_head->prev = temp_node_last;

    printf("rra\n");
}

int main(int n_args, char **args)
{
    List stack_A;
    List stack_B;
    inicialize(&stack_A);
    inicialize(&stack_B);
    if (n_args > 1)
        parsing_stack(&stack_A, args);
    else
        show_error();

    swap_A(&stack_A);
    push_B(&stack_A, &stack_B);
    push_B(&stack_A, &stack_B);
    push_B(&stack_A, &stack_B);

    rotate_A(&stack_A);
    rotate_A(&stack_B);

    reverse_rotate_A(&stack_A);
    reverse_rotate_A(&stack_B);

    swap_A(&stack_A);

    push_A(&stack_A, &stack_B);
    push_A(&stack_A, &stack_B);
    push_A(&stack_A, &stack_B);
    printf("Stack A\n");
    show(stack_A);
    printf("Stack B\n");
    show(stack_B);
    // rotate_A(&stack_A);
    /*
    push_B(&stack_A, &stack_B);
    push_B(&stack_A, &stack_B);
    push_B(&stack_A, &stack_B);
    push_B(&stack_A, &stack_B);

    swap_A_B(&stack_A, &stack_B);
    printf("Stack A\n");
    show(stack_A);
    printf("Stack B\n");
    show(stack_B);
    //swap_A(&stack_A);
    //swap_A(&stack_A);
    //show(stack_A);*/
    free_stack(&stack_A);
    free_stack(&stack_B);
    return (n_args);
}