#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
#include <sys/ioctl.h>
# include <signal.h>
# include <errno.h>
# include <termios.h>   
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

/* ============ ESTRUTURAS ============ */

/* Tipos de tokens */
typedef enum e_token_type
{
	T_WORD,			// comando, argumento
	T_PIPE,			// |
	T_REDIR_IN,		// <
	T_REDIR_OUT,	// >
	T_REDIR_APPEND,	// >>
	T_REDIR_HEREDOC,// <<
	T_EOF			// fim
}	t_token_type;

/* Token - unidade básica do parsing */
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

/* Redirecionamento */
typedef struct s_redir
{
	char			*file;       // Nome do arquivo OU delimiter para heredoc
	t_token_type	type;        // T_REDIR_IN, T_REDIR_OUT, T_REDIR_APPEND, T_REDIR_HEREDOC
	int				fd;          // File descriptor (útil para heredoc)
	int				heredoc_fd;  // FD do pipe para heredoc
	int				expanded;    // Se o delimiter foi expandido (para heredoc)
	struct s_redir	*next;
}	t_redir;

//Estrutura para gerenciar heredocs
typedef struct s_heredoc
{
	char	*delimiter;
	int		fd[2];        // pipe[0] para leitura, pipe[1] para escrita
	int		expanded;     // 1 se delimiter deve expandir variáveis
}	t_heredoc;

/* Comando - unidade de execução */
typedef struct s_command
{
	char				**args;		// array de argumentos
	t_redir				*redirs;	// lista de redirecionamentos
	int					fd_in;		// stdin, pipe ou arquivo
	int					fd_out;		// stdout, pipe ou arquivo
	pid_t				pid;		// PID do processo
	struct s_command	*next;		// próximo comando (pipe)
}	t_command;

typedef enum e_quote_state
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}	t_quote_state;

/* Estado global do shell */
typedef struct s_shell
{
	t_command		*cmd_list;
	char			**env;          // Array para execve
	t_list			*env_list;      // Lista para manipulação (export/unset)
	int				exit_status;
	int				is_interactive;
	char			*line;
	// NOVO: estado do parsing
	t_quote_state	quote_state;
	int				has_unclosed_quote;
}	t_shell;

/* ============ PROTÓTIPOS ============ */

/* ----- main.c ----- */
void	init_shell(t_shell *shell, char **env);
void	cleanup_shell(t_shell *shell);

/* ----- parsing/tokenizer.c ----- */
t_token	*tokenizer(char *line);
void	add_token(t_token **tokens, char *value, t_token_type type);
void	handle_word(t_token **tokens, char *line, int *i);
void	handle_redirection(t_token **tokens, char *line, int *i);
void	cleanup_tokens(t_token *tokens);

/* ----- parsing/parser.c ----- */
t_command	*parser(t_token *tokens, t_shell *shell);
t_command	*create_new_command(void);
void		add_command(t_command **list, t_command *new_cmd);
void		add_argument(t_command *cmd, char *arg);
void		add_redirection(t_command *cmd, t_token *token);
void		cleanup_commands(t_command *cmd);

/* ----- parsing/quote_validator.c ----- */
int	has_unclosed_quotes(char *line);
int	quote_error(void);

/* ----- parsing/quote_expander.c ----- */
char	*remove_quotes(char *str);
char	*expand_quotes(char *word);
void	expand_command_args(t_command *cmd);
void	expand_redir_files(t_command *cmd);


/* ----- parsing/syntax_check.c ----- */
int	syntax_check(t_token *tokens);

/* ----- execution/executor.c ----- */
int		executor(t_shell *shell);
int		is_builtin(char *cmd);
int		execute_builtin(t_shell *shell, t_command *cmd);
void	execute_external(t_command *cmd, char **env);
void	handle_redirs(t_command *cmd);

/* ----- execution/redirections.c ----- */
int		setup_redirections(t_command *cmd, t_shell *shell);  // JÁ CORRIGIDO
void	apply_redirections(t_command *cmd);
void	close_redir_fds(t_command *cmd);

/* ----- execution/heredoc.c ----- */
char	*clean_delimiter(char *delimiter);
int	should_expand_delimiter(char *delimiter);
//int	process_heredoc(char *delimiter, int expanded);
int	process_heredoc(char *delimiter, int expand, t_shell *shell);
char	*get_env_value_from_array(char *var_name, char **env_array);

/* ----- execution/path_finder.c ----- */
char	*find_path(char *cmd, char **env);

/* ----- execution/pipe_executor.c ----- */
int	execute_pipeline(t_shell *shell);
int	execute_single_external(t_shell *shell, t_command *cmd);

/* ----- builtins/ ----- */
int		builtin_echo(t_command *cmd);
int		builtin_pwd(void);
int		builtin_env(char **env);
int		builtin_cd(t_command *cmd, t_shell *shell);
int		builtin_exit(t_shell *shell, t_command *cmd);
int	builtin_export(t_shell *shell, t_command *cmd);
int	builtin_unset(t_shell *shell, t_command *cmd);
int		is_valid_identifier(char *str);

/* ----- signals/signals.c ----- */
void	setup_signals(void);
void	handle_sigint(int sig);

/* ----- utils/memory_utils.c ----- */
void	*ft_malloc(size_t size);
void	free_array(char **array);
void	exit_with_error(char *msg);

/* ----- utils/error_utils.c ----- */
void	print_error(char *cmd, char *msg, int exit_code);
void	print_command_not_found(char *cmd);
void	print_permission_denied(char *cmd);
void	print_cd_error(char *path, char *msg);
void	perror_msg(char *cmd);

/* ----- structures/init.c ----- */
t_shell	*init_shell_data(char **env);
void	init_command(t_command *cmd);

/* ----- structures/cleanup.c ----- */
void	cleanup_all(t_shell *shell, t_token *tokens);

/* ----- environment/env_manager.c ----- */
void	init_env_list(t_shell *shell, char **env);
void	free_env_list(t_list *env_list);
char	*get_env_value(char *var_name, t_shell *shell);
char	**update_env_array(t_shell *shell);
void	set_env_value(t_shell *shell, char *key, char *value);
void	unset_env_value(t_shell *shell, char *key);

/* ----- parser/var_expander.c ----- */
char	*expand_variables(char *str, t_shell *shell);
void	expand_command_vars(t_command *cmd, t_shell *shell);
void	expand_redir_vars(t_command *cmd, t_shell *shell);

#endif
