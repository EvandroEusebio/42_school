#include "minishell.h"

void  free_array(char **arr)
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

char **get_path_env()
{
    char *path_env;
    char **paths;

    path_env = getenv("PATH");
    paths = ft_split(path_env, ':');
    if (!paths)
        return (NULL);
    return(paths);
}

char *find_comand_path(char *cmd)
{
    char **paths;
    int i;
    char *temp;
    char *full_path;

    if (!cmd || *cmd == '\0')
        return (NULL);
    if (cmd[0] == '/' || (cmd[0] == '.' && (cmd[1] == '/'
        || (cmd[1] == '.' && cmd[2] == '/'))))
    {
        if (access(cmd, X_OK) == 0)
            return (ft_strdup(cmd));
        return (NULL);
    }
    i = 0;
    paths = get_path_env();
    if (!paths)
        return (NULL);
    while(paths[i])
    {
        temp = ft_strjoin(paths[i], "/");
        if (!temp)
        {
            free_array(paths);
            return (NULL);
        }
        full_path = ft_strjoin(temp, cmd);
        free(temp);
        if (!full_path)
        {
            free_array(paths);
            return (NULL);
        }
        if(access(full_path, X_OK) == 0)
        {
            free_array(paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    free_array(paths);
    return (NULL);
}


void executor_comand(char *line)
{
    char **args;
    char *cmd_path;
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
        cmd_path = find_comand_path(args[0]);
        if(!cmd_path)
        {
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(args[0], 2);
            ft_putstr_fd(": command not found\n", 2);
            free_array(args);
            exit(127);
        }
        execve(cmd_path, args, NULL);
        perror("execve error");
        free(cmd_path);
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

