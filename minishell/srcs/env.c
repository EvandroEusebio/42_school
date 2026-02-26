#include "minishell.h"

t_env   *create_env_list(char **envp)
{
    t_env *head_env_list;
    t_env *new_env_list;
    char *content_equal_sign;
    int i;

    head_env_list = NULL;
    i = 0;
    while(envp[i])
    {
        content_equal_sign = ft_strchr(envp[i], '=');
        if(content_equal_sign)
        {
            new_env_list = malloc(sizeof(t_env));
            new_env_list->key = ft_substr(envp[i], 0,  content_equal_sign - envp[i]);
            new_env_list->value = ft_strdup(content_equal_sign);
            new_env_list->next = head_env_list;
            head_env_list = new_env_list;
        }
        i++;
    }
    return (head_env_list);
}

void    free_env_list(t_env *env)
{
    t_env   *tmp;

    while (env)
    {
        tmp = env;
        env = env->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
}