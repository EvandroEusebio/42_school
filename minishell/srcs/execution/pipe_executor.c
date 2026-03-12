/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:39:05 by akudiezo          #+#    #+#             */
/*   Updated: 2026/02/18 17:45:24 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

/* Configura os pipes para um comando específico */
static void	setup_pipe_fds(int prev_pipe, int *next_pipe)
{
	// Se há comando anterior, ler do pipe anterior
	if (prev_pipe != -1)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	
	// Se há próximo comando, escrever no próximo pipe
	if (next_pipe)
	{
		close(next_pipe[0]); // Fecha leitura do próximo pipe
		dup2(next_pipe[1], STDOUT_FILENO);
		close(next_pipe[1]);
	}
}

/* Executa um único comando no pipeline */
static void	execute_pipe_command(t_shell *shell, t_command *cmd, 
								int prev_pipe, int *next_pipe)
{
	// Configurar sinais para o filho
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	
	// Configurar FDs do pipe
	setup_pipe_fds(prev_pipe, next_pipe);
	
	// Configurar redirecionamentos (arquivos, heredoc)
	if (setup_redirections(cmd, shell) == -1)
		exit(1);
	
	apply_redirections(cmd);
	
	// Se for builtin no meio do pipe, executar no filho
	if (is_builtin(cmd->args[0]))
	{
		int ret = execute_builtin(shell, cmd);
		exit(ret);
	}
	
	// Comando externo
	execute_external(cmd, shell->env);
}

/* Prepara redirecionamentos de saída no pai (cria/trunca arquivos) */
static int	prepare_output_redirs(t_command *cmd)
{
	t_redir	*redir;
	int		fd;
	
	redir = cmd->redirs;
	while (redir)
	{
		// Apenas redirecionamentos de saída precisam ser preparados no pai
		if (redir->type == T_REDIR_OUT || redir->type == T_REDIR_APPEND)
		{
			if (redir->type == T_REDIR_OUT)
				fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else // T_REDIR_APPEND
				fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			
			if (fd == -1)
			{
				print_error(redir->file, strerror(errno), 1);
				return (-1);
			}
			
			// Guardar fd para usar no filho
			redir->fd = fd;
		}
		redir = redir->next;
	}
	return (0);
}

/* Executa um pipeline completo */
int	execute_pipeline(t_shell *shell)
{
	t_command	*cmd;
	int			prev_pipe;
	int			pipe_fd[2];
	pid_t		pid;
	int			status;
	
	cmd = shell->cmd_list;
	prev_pipe = -1;
	
	// PRIMEIRO: Preparar todos os redirecionamentos de saída no pai
	// Isso cria/trunca os arquivos ANTES de qualquer fork
	t_command *tmp = cmd;
	while (tmp)
	{
		if (prepare_output_redirs(tmp) == -1)
			return (1);
		tmp = tmp->next;
	}
	
	while (cmd)
	{
		// Criar pipe se houver próximo comando
		if (cmd->next)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				return (1);
			}
		}
		
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (1);
		}
		
		if (pid == 0) // Processo filho
		{
			execute_pipe_command(shell, cmd, prev_pipe, 
								cmd->next ? pipe_fd : NULL);
		}
		else // Processo pai
		{
			// Fechar FDs do pipe anterior no pai
			if (prev_pipe != -1)
				close(prev_pipe);
			
			// Fechar lado de escrita do pipe atual (pai não escreve)
			if (cmd->next)
			{
				close(pipe_fd[1]);
				prev_pipe = pipe_fd[0]; // Guardar lado de leitura para próximo
			}
			
			// Fechar FDs de redirecionamento do comando atual
			close_redir_fds(cmd);
			
			// last_pid = pid;
			cmd = cmd->next;
		}
	}
	
	// Fechar último pipe se houver
	if (prev_pipe != -1)
		close(prev_pipe);
	
	// Esperar todos os filhos
	while (wait(&status) > 0);
	
	// Capturar status do último comando
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
	
	return (shell->exit_status);
}
