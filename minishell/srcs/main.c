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

int main(void)
{
    char *line_read;
    signal(SIGINT, handler_sigint);
    signal(SIGQUIT, SIG_IGN);
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
            executor_comand(line_read);
        }
        free(line_read);
    }
    rl_clear_history();
    return (g_shell.g_exit_status);
}