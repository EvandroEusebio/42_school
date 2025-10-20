#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// =======================
// === ESTRUTURAS ========
// =======================

typedef struct node
{
    int v;
    struct node *next;
    struct node *prev;
    int cust_a;
    int cust_b;
    int index;
    int total_cust;
    int pos;
    int target_pos;
} Node;

typedef struct list
{
    Node *begin;
    Node *last;
    int total_elements;
} List;

// =======================
// === FUNÇÕES GERAIS ====
// =======================

void inicialize(List *list);
void show(List list);
void free_stack(List *list);
void show_error(void);
void show_error_and_free(List **stack);
int ft_isdigit(int c);
int ft_atoi(char *str, List **stack);
int is_sorted(List stack);
int absolute_value(int value);
int max_value(int a, int b);
void addIndex(List *stack);
void set_pos(List *stack);

// ============================
// === OPERAÇÕES DE PILHA ====
// ============================

int insert_start(List **list, int v, int index);
int insert_end(List **list, int v, int index);
void verify_duplicate_n(List **list, int number);
void parsing_stack(List *stack, char **args);

// ============================
// === OPERAÇÕES PUSH_SWAP ====
// ============================

// SWAP
void swap_A(List *stack_A);
void swap_B(List *stack_B);
void swap_A_B(List *stack_A, List *stack_B);

// PUSH
void push_A(List *stack_A, List *stack_B);
void push_B(List *stack_A, List *stack_B);

// ROTATE
void rotate(List *stack, char type_stack);
void rotate_r(List *stack_A, List *stack_B);

// REVERSE ROTATE
void reverse_rotate(List *stack, char type_stack);
void reverse_rotate_r(List *stack_A, List *stack_B);

// ============================
// === LÓGICA DO PUSH_SWAP ====
// ============================

void push_swap(List *stack_a, List *stack_b);
void sorted_tree_elements(List *stack);
void operations(List *stack_a, List *stack_b, int cust_a, int cust_b);

// ============================
// === CÁLCULOS DE CUSTO ======
// ============================

int find_min_index(List stack);
int find_max_index(List stack);

// ============================
// === MOVE BACK ======
// ============================
void move_back(List *stack_a, List *stack_b);
void move(List *stack_a, List *stack_b, Node *n);
void get_target_value(List *stack, int value_index, Node *n);
void put_min_top(List *stack);

int c_cust(List stack, int v);

void set_cust(List *stack_a, List *stack_b);
void move_cheap_v(List *stack_a, List *stack_b);
void set_total_cust(Node *n);
void get_cust_top_target(List stack_a, Node *n);
void get_cust_top(int size, Node *n);
void get_target_value(List *stack, int value_index, Node *n);
int get_pos(List stack, int v);



#endif