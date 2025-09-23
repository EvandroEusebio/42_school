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
    // printf("Stack A\n");
    // show(*stack_A);
    // printf("Stack B\n");
    // show(*stack_B);
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
    // printf("Stack A\n");
    // show(*stack_A);
    // printf("Stack B\n");
    // show(*stack_B);
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

// the calcule of the cust in A is diferent of B
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

int pos_fit_value(List stack, int value)
{
    int pos;
    Node *temp_node;

    if (!stack.begin)
        return (0);

    pos = 0;
    temp_node = stack.begin;
    if (value < find_max_value(stack) && value > find_min_value(stack))
    {
        while (temp_node)
        {
            if (value > temp_node->v)
                pos++;
            temp_node = temp_node->next;
        }
    }
    return (pos);
}
// esta a falta o cust B
int calculate_cust_B(List stack, int v_other_stack)
{
    int pos_value;
    // Node *temp_node;
    int cust;
    int max_value;

    if (!stack.begin)
        return (0);
    max_value = find_max_value(stack);
    if (v_other_stack > max_value || v_other_stack < find_min_value(stack))
        return (calculate_cust(stack, max_value));
    pos_value = pos_fit_value(stack, v_other_stack);
    cust = (stack.total_elements) - pos_value;
    if (cust >= pos_value)
        return (pos_value);
    else
        return (-cust);
}

int absolute_value(int value)
{
    if (value < 0)
        return (value * -1);
    return (value);
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
        cust_b = calculate_cust_B(*stack_B, temp_node->v);
        if ((cust_a < 0 && cust_b < 0) || (cust_a > 0 && cust_b > 0))
            total_cust = (absolute_value(cust_a) + absolute_value(cust_b) - 1) + 1;
        else
            total_cust = absolute_value(cust_a) + absolute_value(cust_b) + 1;
        printf("Cust A: %d\n", cust_a);
        printf("Cust B: %d\n", cust_b);
        printf("Total Cust: %d\n", total_cust);
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



// verify if list is sorted
int is_sorted(List stack)
{
    Node *node;

    if(!stack.begin)
    {
        printf("Empty Stack or only value!\n");
        return (0);
    }
    node = stack.begin;
    while (node->next)
    {
        if(node->v > node->next->v)
        {
            printf("Stack not sorted!\n");
            return (0);
        }
        node = node->next;
    }
    printf("Stack sorted!\n");
    return (1);
}

// sorted for list with tree elements
void sorted_tree_elements(List *stack)
{
    int minor_value;
    int max_value;

    minor_value = find_min_value(*stack);
    max_value = find_max_value(*stack);
    if (minor_value == stack->begin->v && max_value == stack->begin->next->v)
    {
        swap_A(stack);
        rotate(stack, 'a');
    }
    else if(minor_value == stack->last->v && max_value == stack->begin->next->v)
        reverse_rotate(stack, 'a');
    else if (max_value == stack->last->v && minor_value == stack->begin->next->v)
        swap_A(stack);
    else
        rotate(stack, 'a');
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

    is_sorted(stack_A);
    printf("================== STACK A before: \n");
    show(stack_A);
    sorted_tree_elements(&stack_A);
    printf("================== STACK A after: \n");
    show(stack_A);
    is_sorted(stack_A);

    

    /*

    is_sorted(stack_A);
    push_B(&stack_A, &stack_B);
    push_B(&stack_A, &stack_B);
    swap_B(&stack_B);
    push_B(&stack_A, &stack_B);
    push_B(&stack_A, &stack_B);
    reverse_rotate(&stack_B, 'b');
    reverse_rotate(&stack_B, 'b');
    push_B(&stack_A, &stack_B);

    printf("STACK A: \n");
    show(stack_A);
    printf("STACK B: \n");
    show(stack_B);

    printf("The value with minor cust is: %d\n", cust_checker(&stack_A, &stack_B));

    printf("================== STACK A: \n");
    show(stack_A);
    printf("================== STACK B: \n");
    show(stack_B);

    
    printf("The value with minor cust is: %d\n", cust_checker(stack_A, stack_B));
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
    // rotate_A(&stack_A);*/
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