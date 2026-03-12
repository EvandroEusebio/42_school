/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:58:43 by akudiezo          #+#    #+#             */
/*   Updated: 2026/01/28 16:58:51 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

/* Encontra caminho completo do comando */
char	*find_path(char *cmd, char **env)
{
	char	*path;
	char	*path_env;
	char	**paths;
	int		i;
	
	// Se já é caminho absoluto ou relativo
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	
	// Buscar PATH no environment
	path_env = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_env = env[i] + 5;
			break;
		}
		i++;
	}
	
	if (!path_env)
		return (NULL);
	
	// Dividir PATH por ':'
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	
	// Tentar cada diretório do PATH
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin3(paths[i], "/", cmd);
		if (access(path, F_OK) == 0)
		{
			free_array(paths);
			return (path);
		}
		free(path);
		i++;
	}
	
	free_array(paths);
	return (NULL);
}
