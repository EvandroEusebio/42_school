#include "minishell.h"

int execute_builtin(char **arg, t_env *g_env)
{
    if (ft_strcmp(arg[0], "echo") == 0)
        return (builtin_echo(arg));
    if (ft_strcmp(arg[0], "pwd") == 0)
        return (builtin_pwd());
    if (ft_strcmp(arg[0], "env") == 0)
        return (builtin_env());
    if (ft_strcmp(arg[0], "cd") == 0)
        return (builtin_cd(arg, g_env));
    return (1);
}

int is_builtin(char *cmd)
{
    if (!cmd)
        return (0);
    if (ft_strcmp(cmd, "echo") == 0 ||
        ft_strcmp(cmd, "pwd") == 0 ||
        ft_strcmp(cmd, "env") == 0 ||
        ft_strcmp(cmd, "cd") == 0)
        return (1);
    return (0);
}

int builtin_echo(char **args)
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
    while (args[i])
    {
        if (ft_strcmp(args[i], "$?") == 0)
            printf("%d", g_shell.g_exit_status);
        else
            printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    if (has_newline)
        printf("\n");
    return (0);
}

int builtin_pwd()
{
    char *cwd;
    cwd = getcwd(NULL, 0);
    if (cwd)
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

void update_old(t_env *env)
{
    char *old_pwd;
    t_env *temp_env_list;

    temp_env_list = env;
    old_pwd = get_env_value(env, "PWD");
    if (old_pwd)
    {
        while (temp_env_list)
        {
            if (ft_strcmp(temp_env_list->key, "OLDPWD") == 0)
            {
                free(temp_env_list->value);
                temp_env_list->value = ft_strdup(old_pwd);
                break;
            }
            temp_env_list = temp_env_list->next;
        }
    }
    else
    {
        printf("OLDPWD nao acessado!\n");
        return;
    }
}

void update_pwd(t_env *env)
{
    char *cwd;
    t_env *temp_env_list;

    temp_env_list = env;

    cwd = getcwd(NULL, 0);
    update_old(env);
    if (cwd)
    {
        while (temp_env_list)
        {
            if (ft_strcmp(temp_env_list->key, "PWD") == 0)
            {
                free(temp_env_list->value);
                temp_env_list->value = ft_strdup(cwd);
                break;
            }
            temp_env_list = temp_env_list->next;
        }
    }
    else
    {
        perror("getcwd");
        return;
    }
    free(cwd);
}

int builtin_cd(char **args, t_env *env)
{
    char *path;
    if (!args[1] || ft_strcmp(args[1], "~") == 0)
    {
        path = get_env_value(env, "HOME");
        printf("PATH: %s\n", path);
        if (!path)
        {
            printf("PATH: %s\n", path);
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
            return (1);
        }
    }
    else if (ft_strcmp(args[1], "-") == 0)
    {
        path = get_env_value(env, "OLDPWD");
        if (!path)
        {
            ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
            return (1);
        }
        // Mostra o path pra onde vai (como bash)
        ft_putstr_fd(path, 1);
        ft_putchar_fd('\n', 1);
    }
    else
        path = args[1];
    if (chdir(path) == -1)
    {
        perror("chdir");
        return (1);
    }
    update_pwd(env);
    return (0);
}

int builtin_env()
{
    t_env *temp_env_list;

    temp_env_list = g_shell.g_env_list;
    while (temp_env_list)
    {
        printf("%s=", temp_env_list->key);
        printf("%s\n", temp_env_list->value);
        temp_env_list = temp_env_list->next;
    }
    return (0);
}
