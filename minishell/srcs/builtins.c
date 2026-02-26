#include "minishell.h"

int     execute_builtin(char **arg)
{
    if(ft_strcmp(arg[0], "echo") == 0)
        return (builtin_echo(arg));
    if(ft_strcmp(arg[0], "pwd") == 0)
        return (builtin_pwd());
    if(ft_strcmp(arg[0], "env") == 0)
        return (builtin_env());
    return (1);
}

int is_builtin(char *cmd)
{
    if (!cmd)
        return (0);
    if (ft_strcmp(cmd, "echo") == 0 ||
        ft_strcmp(cmd, "pwd") == 0 ||
        ft_strcmp(cmd, "env") == 0)
        return (1);
    return (0);
}

int     builtin_echo(char **args)
{
    int has_newline;
    int i;

    i = 1;
    has_newline = 1;
    if (args[1] && (ft_strcmp(args[1], "-n") == 0))
    {
        i = 2;
        has_newline = 0;
    }
    while(args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    if (has_newline)
        printf("\n");
    return (0);
}

int     builtin_pwd()
{
    char *cwd;
    cwd = getcwd(NULL, 0);
    if(cwd)
    {
        printf("%s\n", cwd);
        free(cwd);
    }
    else
    {
        perror("getcwd");
        return (1);
    }
    return (0);
}


int     builtin_env()
{
    t_env *temp_env_list;

    temp_env_list = g_shell.g_env_list;
    while(temp_env_list)
    {
        printf("%s=", temp_env_list->key);
        printf("%s\n", temp_env_list->value);
        temp_env_list = temp_env_list->next;
    }
    return (0);
}