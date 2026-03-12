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

static int verify_args(char **args)
{
	int quant_args;

	quant_args = 0;
	while(args[quant_args])
		quant_args++;
	if (quant_args > 2)
		return (1);
	return (0);
}

int	builtin_cd(t_command *cmd, t_shell *shell)
{
	char *target;
	char *oldpwd;
	char *tmp;
	int   ret;

	if (!cmd || !shell)
		return (1);
	if(verify_args(cmd->args) == 1)
	{
		print_cd_error(NULL, "too many arguments");
		return (1);
	}
	if (!cmd->args[1] || cmd->args[1][0] == '\0' || ft_strncmp(cmd->args[1], "~", 2) == 0)
	{
		target = get_env_value("HOME", shell);
		if (!target || *target == '\0')
		{
			print_cd_error(NULL, "HOME not set");
			free(target);
			return (1);
		}
	}
	else if (ft_strncmp(cmd->args[1], "-", 2) == 0)
	{
		target = get_env_value("OLDPWD", shell);
		if (!target || *target == '\0')
		{
			print_cd_error(NULL, "OLDPWD not set");
			free(target);
			return (1);
		}
		printf("%s\n", target);
	}
	else
		target = ft_strdup(cmd->args[1]);

	oldpwd = getcwd(NULL, 0);
	ret = chdir(target);
	if (ret == -1)
	{
		print_cd_error(target, strerror(errno));
		free(target);
		free(oldpwd);
		return (1);
	}
	tmp = getcwd(NULL, 0);
	if (oldpwd)
		set_env_value(shell, "OLDPWD", oldpwd);
	if (tmp)
		set_env_value(shell, "PWD", tmp);
	free(oldpwd);
	free(tmp);
	free(target);
	return (0);
}