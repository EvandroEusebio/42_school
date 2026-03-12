/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:15:06 by ieusebio          #+#    #+#             */
/*   Updated: 2026/03/04 15:15:07 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./../../minishell.h"

int	builtin_unset(t_shell *shell, t_command *cmd)
{
	int i;
	char *arg;
	int ret;

	if (!cmd || !shell)
		return (1);
	ret = 0;
	i = 1;
	while (cmd->args[i])
	{
		arg = cmd->args[i];
		if (!is_valid_identifier(arg))
		{
			print_error("unset", "not a valid identifier", 1);
			ret = 1;
		}
		else
			unset_env_value(shell, arg);
		i++;
	}
	return (ret);
}
