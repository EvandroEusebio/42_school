/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:24:29 by akudiezo          #+#    #+#             */
/*   Updated: 2026/02/12 16:31:39 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

/* Processa redirecionamento de input (<) */
static int	handle_input_redir(char *file)
{
	int	fd;
	
	if (!file || file[0] == '\0')
	{
		print_error("", "ambiguous redirect", 1);
		return (-1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
		print_error(file, strerror(errno), 1);
	return (fd);
}

/* Processa redirecionamento de output (>) */
static int	handle_output_redir(char *file)
{
	int	fd;
	
	if (!file || file[0] == '\0')
	{
		print_error("", "ambiguous redirect", 1);
		return (-1);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		print_error(file, strerror(errno), 1);
	return (fd);
}

/* Processa redirecionamento de append (>>) */
static int	handle_append_redir(char *file)
{
	int	fd;
	
	if (!file || file[0] == '\0')
	{
		print_error("", "ambiguous redirect", 1);
		return (-1);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		print_error(file, strerror(errno), 1);
	return (fd);
}

/* Processa heredoc (<<) */
static int	handle_heredoc_redir(t_redir *redir, t_shell *shell)  // <-- ADICIONAR PARÂMETRO
{
	int		fd;
	char	*delimiter;
	int		expanded;
	
	if (!redir || !redir->file)
		return (-1);
	
	delimiter = clean_delimiter(redir->file);
	if (!delimiter)
		return (-1);
	
	expanded = should_expand_delimiter(redir->file);
	fd = process_heredoc(delimiter, expanded, shell);  // <-- PASSAR SHELL
	
	free(delimiter);
	
	if (fd == -1)
		return (-1);
	
	return (fd);
}

/* Configura todos os redirecionamentos (abre arquivos) */
int	setup_redirections(t_command *cmd, t_shell *shell)  // <-- ADICIONAR PARÂMETRO
{
	t_redir	*redir;
	int		fd;
	
	if (!cmd)
		return (-1);
	
	redir = cmd->redirs;
	
	while (redir)
	{
		fd = -1;
		
		if (redir->type == T_REDIR_IN)
			fd = handle_input_redir(redir->file);
		else if (redir->type == T_REDIR_OUT)
			fd = handle_output_redir(redir->file);
		else if (redir->type == T_REDIR_APPEND)
			fd = handle_append_redir(redir->file);
		else if (redir->type == T_REDIR_HEREDOC)
			fd = handle_heredoc_redir(redir, shell);  // <-- PASSAR SHELL
		
		if (fd == -1)
			return (-1);
		
		// Guardar o fd no redir
		redir->fd = fd;
		
		redir = redir->next;
	}
	
	return (0);
}

/* Aplica os redirecionamentos no processo atual */
void	apply_redirections(t_command *cmd)
{
	t_redir	*redir;
	
	if (!cmd)
		return;
	
	redir = cmd->redirs;
	
	while (redir)
	{
		if (redir->type == T_REDIR_IN || redir->type == T_REDIR_HEREDOC)
		{
			// Redirecionar entrada
			if (dup2(redir->fd, STDIN_FILENO) == -1)
			{
				print_error("dup2", strerror(errno), 1);
				exit(1);
			}
		}
		else if (redir->type == T_REDIR_OUT || redir->type == T_REDIR_APPEND)
		{
			// Redirecionar saída
			if (dup2(redir->fd, STDOUT_FILENO) == -1)
			{
				print_error("dup2", strerror(errno), 1);
				exit(1);
			}
		}
		
		// Fechar o fd original (já não é necessário)
		close(redir->fd);
		redir->fd = -1;
		
		redir = redir->next;
	}
}

/* Fecha FDs de redirecionamento no processo pai */
void	close_redir_fds(t_command *cmd)
{
	t_redir	*redir;
	
	if (!cmd)
		return;
	
	redir = cmd->redirs;
	
	while (redir)
	{
		if (redir->fd != -1)
		{
			close(redir->fd);
			redir->fd = -1;
		}
		redir = redir->next;
	}
}
