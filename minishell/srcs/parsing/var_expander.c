/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 18:41:42 by akudiezo          #+#    #+#             */
/*   Updated: 2026/02/20 18:42:47 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

/* Expande uma variável $NAME */
static char	*expand_var(char *str, int *i, t_shell *shell)
{
	int		start;
	char	*var_name;
	char	*value;
	
	(*i)++; // Pular o $
	start = *i;
	
	// Caso especial: $$ (PID do shell)
	if (str[*i] == '$')
	{
		(*i)++;
		return (ft_itoa(getpid())); // Retorna o PID do processo
	}
	
	// Caso especial: $? (exit status)
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->exit_status));
	}
	
	// Nome da variável: letras, números, underscore
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	
	if (*i == start) // $ sozinho
		return (ft_strdup("$"));
	
	var_name = ft_substr(str, start, *i - start);
	value = get_env_value(var_name, shell);
	free(var_name);
	
	if (!value)
		return (ft_strdup("")); // Variável não definida = string vazia
	
	return (value);
}

/* Adiciona um caractere à string 
static char	*append_char(char *str, char c)
{
	char	*new_str;
	char	tmp[2];
	
	tmp[0] = c;
	tmp[1] = '\0';
	new_str = ft_strjoin(str, tmp);
	free(str);
	return (new_str);
}*/

/* Expande variáveis em uma string, respeitando quotes e escapes */
char	*expand_variables(char *str, t_shell *shell)
{
	int		i;
	int		in_single_quote;
	int		in_double_quote;
	int		escape_next;
	char	*result;
	char	*expanded_part;
	char	*temp;
	char	char_str[2];
	
	if (!str)
		return (NULL);
	
	result = ft_strdup("");
	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	escape_next = 0;
	
	while (str[i])
	{
		// Tratar escape character
		if (str[i] == '\\' && !escape_next && !in_single_quote)
		{
			// Verificar próximo caractere
			if (str[i + 1])
			{
				// Dentro de double quotes, caracteres especiais são escapados
				if (in_double_quote)
				{
					// Caracteres que precisam de escape dentro de double quotes
					if (str[i + 1] == '"' || str[i + 1] == '\\' || 
						str[i + 1] == '$' || str[i + 1] == '`')
					{
						// Pular o backslash e adicionar o próximo caractere literalmente
						i++;
						char_str[0] = str[i];
						char_str[1] = '\0';
						temp = ft_strjoin(result, char_str);
						free(result);
						result = temp;
						i++;
						continue;
					}
				}
				else
				{
					// Fora de quotes, backslash escapa o próximo caractere
					i++;
					char_str[0] = str[i];
					char_str[1] = '\0';
					temp = ft_strjoin(result, char_str);
					free(result);
					result = temp;
					i++;
					continue;
				}
			}
		}
		
		// Controlar estado das quotes
		if (!escape_next)
		{
			if (str[i] == '\'' && !in_double_quote)
			{
				in_single_quote = !in_single_quote;
				// NÃO adicionar a quote ao resultado
				i++;
				continue;
			}
			else if (str[i] == '"' && !in_single_quote)
			{
				in_double_quote = !in_double_quote;
				// NÃO adicionar a quote ao resultado
				i++;
				continue;
			}
		}
		
		// Encontrou $ para expandir (fora de single quotes e não escapado)
		if (str[i] == '$' && !in_single_quote && !escape_next)
		{
			// Verificar se o $ está escapado
			if (i > 0 && str[i - 1] == '\\' && in_double_quote)
			{
				// $ escapado, tratar como literal
				char_str[0] = '$';
				char_str[1] = '\0';
				temp = ft_strjoin(result, char_str);
				free(result);
				result = temp;
				i++;
			}
			else
			{
				expanded_part = expand_var(str, &i, shell);
				if (expanded_part)
				{
					temp = ft_strjoin(result, expanded_part);
					free(result);
					free(expanded_part);
					result = temp;
				}
			}
		}
		else
		{
			// Caractere normal
			char_str[0] = str[i];
			char_str[1] = '\0';
			temp = ft_strjoin(result, char_str);
			free(result);
			result = temp;
			i++;
		}
		
		escape_next = 0;
	}
	
	return (result);
}

/* Expande variáveis em todos os argumentos de um comando */
void	expand_command_vars(t_command *cmd, t_shell *shell)
{
	int		i;
	char	*expanded;
	
	if (!cmd || !cmd->args)
		return;
	
	i = 0;
	while (cmd->args[i])
	{
		expanded = expand_variables(cmd->args[i], shell);
		if (expanded)
		{
			free(cmd->args[i]);
			cmd->args[i] = expanded;
		}
		i++;
	}
}

/* Expande variáveis em redirecionamentos (exceto heredoc delimiter) */
void	expand_redir_vars(t_command *cmd, t_shell *shell)
{
	t_redir	*redir;
	char	*expanded;
	
	if (!cmd || !cmd->redirs)
		return;
	
	redir = cmd->redirs;
	while (redir)
	{
		// Heredoc delimiter NÃO expande variáveis (a menos que sem quotes)
		if (redir->type == T_REDIR_HEREDOC)
		{
			if (redir->expanded) // Sem quotes, pode expandir no conteúdo
				redir->expanded = 1; // Marcamos para expandir no conteúdo depois
			// O delimiter em si não expande
		}
		else if (redir->file)
		{
			expanded = expand_variables(redir->file, shell);
			if (expanded)
			{
				free(redir->file);
				redir->file = expanded;
			}
		}
		redir = redir->next;
	}
}
