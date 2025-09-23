

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