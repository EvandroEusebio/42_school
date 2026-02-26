#include "minishell.h"

t_shell g_shell = {0};

void handler_sigint(int signal)
{
        (void)signal;
        if(g_shell.g_in_child == 0)
        {
            write(1, "\n", 1);
            rl_replace_line("", 0);
            rl_on_new_line();
            rl_redisplay();
        }
}

int main(int argc, char **argv, char **envp)
{
    char *line_read;
    char **args;
    (void)argc;
    (void)argv;
    signal(SIGINT, handler_sigint);
    signal(SIGQUIT, SIG_IGN);

    g_shell.g_env_list = NULL;
    g_shell.g_env_list = create_env_list(envp);
    if (!g_shell.g_env_list)
        return (1);

    while(1)
    {
        line_read = readline("PROMPT > ");
        if(!line_read)
        {
            printf("exit\n");
            break;
        }
        if(*line_read)
        {
            add_history(line_read);
            args = ft_split(line_read, ' ');
            if(args)
            {
                if(is_builtin(args[0]))
                    g_shell.g_exit_status = execute_builtin(args);
                else
                    executor_comand(line_read);
                free_array(args);
            }
        }
        free(line_read);
    }
    rl_clear_history();
    free_env_list(g_shell.g_env_list);
    return (g_shell.g_exit_status);
}