#include "minishell.h"

void    free_array(char **arr)
{
    int i = 0;

    if (!arr)
        return ;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void executor_comand(char *line)
{
    char **args;
    int status;
    pid_t pid;

    args = ft_split(line, ' ');
    if(!args)
        return ;
    g_shell.g_in_child = 1;
    pid = fork();
    if (pid == -1)
    {
        perror("fork error");
        free_array(args);
        g_shell.g_in_child = 0;
        return ;
    }
    if(pid == 0)
    {
        execve(args[0], args, NULL);
        perror("execve error");
        free_array(args);
        exit(127);
    }
    else
    {
        waitpid(pid, &status, 0);
        if(WIFEXITED(status))
            g_shell.g_exit_status = WEXITSTATUS(status);
        else if(WIFSIGNALED(status))
            g_shell.g_exit_status = 128 + WTERMSIG(status);
        g_shell.g_in_child = 0;
    }
    free_array(args);
}