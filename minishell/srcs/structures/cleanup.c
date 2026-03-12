/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:53:57 by akudiezo          #+#    #+#             */
/*   Updated: 2026/01/28 16:54:02 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void	cleanup_shell(t_shell *shell)
{
	if (shell->env)
		free_array(shell->env);
	if (shell->line)
		free(shell->line);
	cleanup_commands(shell->cmd_list);
	rl_clear_history();
}

void	cleanup_tokens(t_token *tokens)
{
	t_token	*tmp;
	
	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->value)
			free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

void	cleanup_commands(t_command *cmd)
{
	t_command	*tmp;
	t_redir		*redir_tmp;
	
	while (cmd)
	{
		tmp = cmd->next;
		
		// Liberar args
		if (cmd->args)
			free_array(cmd->args);
		
		// Liberar redirecionamentos
		while (cmd->redirs)
		{
			redir_tmp = cmd->redirs->next;
			if (cmd->redirs->file)
				free(cmd->redirs->file);
			// Fechar fd de heredoc se ainda estiver aberto
			if (cmd->redirs->heredoc_fd > 2)
				close(cmd->redirs->heredoc_fd);
			free(cmd->redirs);
			cmd->redirs = redir_tmp;
		}
		
		// Fechar FDs
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		
		free(cmd);
		cmd = tmp;
	}
}
