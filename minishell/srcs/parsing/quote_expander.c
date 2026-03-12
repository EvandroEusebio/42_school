/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:48:26 by akudiezo          #+#    #+#             */
/*   Updated: 2026/02/12 13:49:10 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

/* Remove quotes de uma string e retorna nova string sem as quotes */
/* Remove quotes de uma string, respeitando escapes */
char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	int		in_single;
	int		in_double;
	int		escape_next;
	char	*result;
	
	if (!str)
		return (NULL);
	
	result = (char *)malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	
	i = 0;
	j = 0;
	in_single = 0;
	in_double = 0;
	escape_next = 0;
	
	while (str[i])
	{
		// Tratar escape
		if (str[i] == '\\' && !escape_next && !in_single)
		{
			if (in_double)
			{
				// Dentro de double quotes, só escapa ", \, $, `
				if (str[i + 1] == '"' || str[i + 1] == '\\' || str[i + 1] == '$' || str[i + 1] == '`')
				{
					escape_next = 1;
					i++;
					continue;
				}
			}
			else
			{
				escape_next = 1;
				i++;
				continue;
			}
		}
		
		// Controlar quotes (apenas se não for escaped)
		if (!escape_next)
		{
			if (str[i] == '\'' && !in_double)
			{
				in_single = !in_single;
				i++;
				continue;
			}
			if (str[i] == '"' && !in_single)
			{
				in_double = !in_double;
				i++;
				continue;
			}
		}
		
		// Caractere normal ou escapado
		result[j++] = str[i++];
		escape_next = 0;
	}
	
	result[j] = '\0';
	return (result);
}

/* Expande uma palavra processando quotes */
char	*expand_quotes(char *word)
{
	char	*expanded;
	
	if (!word)
		return (NULL);
	
	// Por enquanto só remove quotes
	// Na Semana 3, aqui também expandiremos variáveis $ dentro de double quotes
	expanded = remove_quotes(word);
	
	return (expanded);
}

/* Processa todos os argumentos de um comando */
void	expand_command_args(t_command *cmd)
{
	int		i;
	char	*expanded;
	
	if (!cmd || !cmd->args)
		return;
	
	i = 0;
	while (cmd->args[i])
	{
		expanded = expand_quotes(cmd->args[i]);
		if (expanded)
		{
			free(cmd->args[i]);
			cmd->args[i] = expanded;
		}
		i++;
	}
}

/* Processa todos os redirecionamentos de um comando */
void	expand_redir_files(t_command *cmd)
{
	t_redir	*redir;
	char	*expanded;
	
	if (!cmd || !cmd->redirs)
		return;
	
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->file)
		{
			expanded = expand_quotes(redir->file);
			if (expanded)
			{
				free(redir->file);
				redir->file = expanded;
			}
		}
		redir = redir->next;
	}
}
