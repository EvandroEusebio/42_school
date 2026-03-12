/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:55:15 by akudiezo          #+#    #+#             */
/*   Updated: 2026/02/12 12:43:52 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

/* Adiciona novo token à lista */
void	add_token(t_token **tokens, char *value, t_token_type type)
{
	t_token	*new_token;
	t_token	*last;
	
	new_token = (t_token *)ft_malloc(sizeof(t_token));
	new_token->value = NULL;
	if (value)
		new_token->value = ft_strdup(value);
	new_token->type = type;
	new_token->next = NULL;
	
	if (!*tokens)
		*tokens = new_token;
	else
	{
		last = *tokens;
		while (last->next)
			last = last->next;
		last->next = new_token;
	}
}

/* Identifica redirecionamentos: <, <<, >, >> */
void	handle_redirection(t_token **tokens, char *line, int *i)
{
	if (line[*i] == '<')
	{
		if (line[*i + 1] == '<')
		{
			add_token(tokens, "<<", T_REDIR_HEREDOC);
			(*i) += 2;
		}
		else
		{
			add_token(tokens, "<", T_REDIR_IN);
			(*i) += 1;
		}
	}
	else if (line[*i] == '>')
	{
		if (line[*i + 1] == '>')
		{
			add_token(tokens, ">>", T_REDIR_APPEND);
			(*i) += 2;
		}
		else
		{
			add_token(tokens, ">", T_REDIR_OUT);
			(*i) += 1;
		}
	}
}

/* Identifica palavras (com tratamento básico de quotes) */
void	handle_word(t_token **tokens, char *line, int *i)
{
	int		start;
	int		in_single;
	int		in_double;
	char	*word;
	
	start = *i;
	in_single = 0;
	in_double = 0;
	
	while (line[*i])
	{
		// Se não está em quote, verifica delimitadores
		if (!in_single && !in_double)
		{
			if (ft_isspace(line[*i]) || line[*i] == '|' 
				|| line[*i] == '<' || line[*i] == '>')
				break;
		}
		
		// Toggle single quote (se não está em double)
		if (line[*i] == '\'' && !in_double)
			in_single = !in_single;
		// Toggle double quote (se não está em single)
		else if (line[*i] == '"' && !in_single)
			in_double = !in_double;
		
		(*i)++;
	}
	
	// Extrair a palavra COMPLETA (incluindo as quotes)
	if (*i > start)
	{
		word = ft_substr(line, start, *i - start);
		add_token(tokens, word, T_WORD);
		free(word);
	}
}

/* Tokenizer principal */
t_token	*tokenizer(char *line)
{
	t_token	*tokens;
	int		i;
	
	tokens = NULL;
	i = 0;
	
	while (line[i])
	{
		// Pular espaços
		while (ft_isspace(line[i]))
			i++;
		
		// Verificar fim da linha
		if (!line[i])
			break;
		
		// Identificar token
		if (line[i] == '|')
		{
			add_token(&tokens, "|", T_PIPE);
			i++;
		}
		else if (line[i] == '<' || line[i] == '>')
			handle_redirection(&tokens, line, &i);
		else
			handle_word(&tokens, line, &i);
	}
	
	// Adicionar token EOF
	add_token(&tokens, NULL, T_EOF);
	return (tokens);
}
