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


typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
}                   t_env;


typedef struct s_shell
{
    int g_exit_status;
    int g_in_child;
    t_env *g_env_list;

} t_shell;


extern t_shell g_shell;


// BUILTINS
int     builtin_echo(char **args);
int     builtin_pwd(void);
//int     builtin_env(t_env *env);
int     builtin_env();
t_env   *create_env_list(char **envp);
int     is_builtin(char *arg);
int     execute_builtin(char **arg);
void    free_env_list(t_env *env);
 

void free_array(char **arr);
void executor_comand(char *line);
char *find_comand_path(char *cmd);
char **get_path_env();

#endif