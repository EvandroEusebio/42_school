/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:25:55 by akudiezo          #+#    #+#             */
/*   Updated: 2026/02/12 12:26:10 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

/* Verifica se todas as quotes estão fechadas na linha */
int	has_unclosed_quotes(char *line)
{
	int				i;
	int				in_single;
	int				in_double;
	
	i = 0;
	in_single = 0;
	in_double = 0;
	
	while (line[i])
	{
		// Escape character - pular próximo caractere (para Semana 3)
		if (line[i] == '\\' && !in_single)
		{
			if (line[i + 1])
				i += 2;
			else
				i++;
			continue;
		}
		
		// Single quote
		if (line[i] == '\'' && !in_double)
			in_single = !in_single;
		// Double quote
		else if (line[i] == '"' && !in_single)
			in_double = !in_double;
		
		i++;
	}
	
	return (in_single || in_double);
}

/* Função auxiliar para mensagem de erro */
int	quote_error(void)
{
	printf("minishell: syntax error: unclosed quotes\n");
	return (1);
}
