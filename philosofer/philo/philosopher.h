#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include "stdlib.h"
#include "stdio.h"
#include "pthread.h"
#include "unistd.h"

typedef struct s_philosopher
{
    int id;
    int is_eat;
    int is_sleep;
    int is_think;
};



#endif