#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>

# include "../libft/libft.h"


typedef struct s_shell
{
    int g_exit_status;
    int g_in_child;

} t_shell;

extern t_shell g_shell;

// Protótipos vão vir aqui depois
 

void free_array(char **arr);
void executor_comand(char *line);
char *find_comand_path(char *cmd);
char **get_path_env();

#endif