#include "minishell.h"

void handler_sigint(int signal)
{
        (void)signal;
        write(1, "\n", 1);
        rl_replace_line(" ", 0);
        rl_on_new_line();
        rl_redisplay();
}

// void handler_sigquit(int signal)
// {
//         (void)signal;
        
// }

int main(void)
{
    char *line_read;
    signal(SIGINT, handler_sigint);
    signal(SIGQUIT, SIG_IGN);
    while(1)
    {
        line_read = readline("PROMPT > ");
        if(!line_read)
            break;
        if(*line_read)
            add_history(line_read);
        printf("Line Read: %s\n", line_read);
        free(line_read);
    }
    rl_clear_history();
    return (0);
}