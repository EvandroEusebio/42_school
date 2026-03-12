/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:57:34 by akudiezo          #+#    #+#             */
/*   Updated: 2026/01/28 16:57:47 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

/* Verifica se é builtin */
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

/* Executa builtin */
int	execute_builtin(t_shell *shell, t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(cmd));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (builtin_env(shell->env));
	else if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
		return (builtin_cd(cmd, shell));
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0)
		return (builtin_export(shell, cmd));
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
		return (builtin_unset(shell, cmd));
	else if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
		return (builtin_exit(shell, cmd));
	// Outros builtins
	return (0);
}

/* Aplica redirecionamentos */
void	handle_redirs(t_command *cmd)
{
	t_redir	*redir;
	int		fd;
	
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == T_REDIR_IN)
			fd = open(redir->file, O_RDONLY);
		else if (redir->type == T_REDIR_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == T_REDIR_APPEND)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		// T_REDIR_HEREDOC ainda não implementado
		
		if (fd == -1)
		{
			perror(redir->file);
			exit(1);
		}
		
		// Redirecionar stdin ou stdout
		if (redir->type == T_REDIR_IN || redir->type == T_REDIR_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		
		close(fd);
		redir = redir->next;
	}
}

/* Processa comandos sem argumentos (só redirecionamentos) */
static int	handle_redir_only(t_command *cmd, t_shell *shell)
{
	if (!cmd || !cmd->redirs)
		return (0);
	
	// Configurar redirecionamentos (cria o pipe com o conteúdo do heredoc)
	if (setup_redirections(cmd, shell) == -1)
		return (1);
	
	// NÃO LER O PIPE! Apenas fechar os FDs.
	// O conteúdo do heredoc já foi escrito no pipe pelo filho,
	// mas como não há comando para ler, simplesmente descartamos.
	close_redir_fds(cmd);
	
	// Garantir que o terminal esteja limpo
	tcflush(STDIN_FILENO, TCIFLUSH);
	
	return (0);
}

/* Executa comando externo */
void	execute_external(t_command *cmd, char **env)
{
	char	*path;
	
	// Encontrar caminho do comando
	path = find_path(cmd->args[0], env);
	if (!path)
	{
		print_command_not_found(cmd->args[0]);
		exit(127);
	}
	
	// Executar
	execve(path, cmd->args, env);
	
	// Se execve falhar
	perror_msg(cmd->args[0]);
	exit(126);
}

/* Executa builtin com redirecionamentos */
static int	execute_builtin_with_redirs(t_shell *shell, t_command *cmd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;
	
	// Salvar FDs originais
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	
	// Configurar redirecionamentos
	if (setup_redirections(cmd, shell) == -1)
	{
		close(saved_stdin);
		close(saved_stdout);
		shell->exit_status = 1;
		return (1);
	}
	
	// Aplicar redirecionamentos
	apply_redirections(cmd);
	
	// Executar builtin
	ret = execute_builtin(shell, cmd);
	
	// Restaurar FDs originais
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	
	shell->exit_status = ret;
	return (ret);
}

/* Executa comando externo com redirecionamentos */
void	execute_external_with_redirs(t_command *cmd, t_shell *shell)
{
	// Configurar redirecionamentos
	if (setup_redirections(cmd, shell) == -1)
		exit(1);
	
	// Aplicar redirecionamentos
	apply_redirections(cmd);
	
	// Executar comando
	execute_external(cmd, shell->env);
}

/* Executa um comando externo único (sem pipe) */
int	execute_single_external(t_shell *shell, t_command *cmd)
{
	pid_t	pid;
	int		status;
	
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	
	if (pid == 0) // Processo filho
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		
		if (setup_redirections(cmd, shell) == -1)
			exit(1);
		
		apply_redirections(cmd);
		execute_external(cmd, shell->env);
	}
	else // Processo pai
	{
		signal(SIGINT, SIG_IGN);
		close_redir_fds(cmd);
		waitpid(pid, &status, 0);
		setup_signals();
		
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exit_status = 128 + WTERMSIG(status); // <-- JÁ DEVE ESTAR AQUI
		else
			shell->exit_status = 1;
	}
	
	return (shell->exit_status);
}


/* Executor principal */
int	executor(t_shell *shell)
{
	t_command	*cmd;
	//pid_t		pid;
	//int			status;
	
	if (!shell || !shell->cmd_list)
		return (1);
	
	cmd = shell->cmd_list;
	
	// Caso 1: Comando sem argumentos (só redirecionamentos)
	if (!cmd->args || !cmd->args[0])
		return (handle_redir_only(cmd, shell));
		
	// Caso 2: Pipeline com múltiplos comandos
	if (cmd->next)
		return (execute_pipeline(shell));
	
	// Caso 3: Builtin sem pipe
	if (is_builtin(cmd->args[0]) && !cmd->next)
		return (execute_builtin_with_redirs(shell, cmd));
	
	// Caso 4: Comando externo único sem pipe
	return (execute_single_external(shell, cmd));
}
