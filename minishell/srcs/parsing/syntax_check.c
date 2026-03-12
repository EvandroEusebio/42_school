/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:56:32 by akudiezo          #+#    #+#             */
/*   Updated: 2026/01/28 16:56:57 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

static int	is_redirection(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT
		|| type == T_REDIR_APPEND || type == T_REDIR_HEREDOC);
}

int	syntax_check(t_token *tokens)
{
	t_token	*current;
	
	current = tokens;
	
	// Caso 1: Pipe no início
	if (current && current->type == T_PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	
	// Caso 2: Redirecionamento sem arquivo
	while (current)
	{
		if (is_redirection(current->type))
		{
			if (!current->next || current->next->type != T_WORD)
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				return (1);
			}
		}
		// Caso 3: Pipe seguido de pipe
		if (current->type == T_PIPE)
		{
			if (!current->next || current->next->type == T_PIPE)
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (1);
			}
		}
		current = current->next;
	}
	
	return (0); // Sintaxe OK
}
