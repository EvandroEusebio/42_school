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

int	builtin_echo(t_command *cmd)
{
	int	i;
	int	newline;
	
	newline = 1;
	i = 1;

	// Verificar opção -n
	if (cmd->args[1] && ft_strcmp(cmd->args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	
	// Imprimir argumentos
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])	
			printf(" ");
		i++;
	}
	
	if (newline)
		printf("\n");
	return (0);
}