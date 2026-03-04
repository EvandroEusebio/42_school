#include "minishell.h"

char    *get_env_value(t_env *env, char *key)
{
    t_env *current = env;

    while(current)
    {
        if(ft_strcmp(current->key, key) == 0)
        {
            return (current->value + 1);
        }
        current = current->next;
    }
    return (NULL);
}