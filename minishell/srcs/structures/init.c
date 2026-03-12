/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:52:04 by akudiezo          #+#    #+#             */
/*   Updated: 2026/01/28 16:52:26 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void	init_shell(t_shell *shell, char **env)
{
	shell->cmd_list = NULL;
	shell->exit_status = 0;
	shell->is_interactive = isatty(STDIN_FILENO);
	shell->line = NULL;
	
	// Copiar environment
	int i = 0;
	while (env[i])
		i++;
	shell->env = (char **)ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (env[i])
	{
		shell->env[i] = ft_strdup(env[i]);
		i++;
	}
	shell->env[i] = NULL;
}

void	init_command(t_command *cmd)
{
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->pid = -1;
	cmd->next = NULL;
}
