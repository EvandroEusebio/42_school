/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:00:13 by akudiezo          #+#    #+#             */
/*   Updated: 2026/01/28 17:01:00 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

int	builtin_exit(t_shell *shell, t_command *cmd)
{
	long status;
	char *arg;
	int   i;

	(void)cmd;
	printf("exit\n");
	status = shell->exit_status;
	if (cmd && cmd->args[1])
	{
		arg = cmd->args[1];
		i = 0;
		if (arg[0] == '+' || arg[0] == '-')
			i++;
		while (arg[i] && ft_isdigit(arg[i]))
			i++;
		if (arg[i] != '\0')
		{
			print_error("exit", "numeric argument required", 255);
			cleanup_shell(shell);
			free_env_list(shell->env_list);
			exit(255);
		}
		status = ft_atoi(arg);
		if (cmd->args[2])
		{
			print_error("exit", "too many arguments", 1);
			shell->exit_status = 1;
			return (1);
		}
	}
	cleanup_shell(shell);
	free_env_list(shell->env_list);
	exit(status);
}