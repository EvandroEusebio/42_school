/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:14:38 by ieusebio          #+#    #+#             */
/*   Updated: 2026/03/04 15:14:42 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./../../minishell.h"

int	builtin_export(t_shell *shell, t_command *cmd)
{
	int i;
	int ret;
	char *arg;
	char *equals;
	char *key;
	char *value;

	if (!cmd || !shell)
		return (1);
	ret = 0;
	/* sem argumentos -> imprimir todas as variáveis */
	if (!cmd->args[1])
	{
		t_list *tmp = shell->env_list;
		while (tmp)
		{
			char *entry = (char *)tmp->content;
			equals = ft_strchr(entry, '=');
			if (equals)
			{
				key = ft_substr(entry, 0, equals - entry);
				value = ft_strdup(equals + 1);
				printf("declare -x %s=\"%s\"\n", key, value);
				free(key);
				free(value);
			}
			else
				printf("declare -x %s\n", entry);
			tmp = tmp->next;
		}
		return (0);
	}
	i = 1;
	while (cmd->args[i])
	{
		arg = cmd->args[i];
		equals = ft_strchr(arg, '=');
		if (equals)
		{
			key = ft_substr(arg, 0, equals - arg);
			value = ft_strdup(equals + 1);
		}
		else
		{
			key = ft_strdup(arg);
			value = NULL;
		}
		if (!is_valid_identifier(key))
		{
			print_error("export", "not a valid identifier", 1);
			ret = 1;
		}
		else
		{
			set_env_value(shell, key, value);
		}
		free(key);
		if (value)
			free(value);
		i++;
	}
	return (ret);
}
