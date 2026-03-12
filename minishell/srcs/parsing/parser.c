/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:55:41 by akudiezo          #+#    #+#             */
/*   Updated: 2026/02/12 13:53:12 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

/* Cria novo comando vazio */
t_command	*create_new_command(void)
{
	t_command	*cmd;
	
	cmd = (t_command *)ft_malloc(sizeof(t_command));
	init_command(cmd);
	return (cmd);
}

/* Adiciona comando à lista */
void	add_command(t_command **list, t_command *new_cmd)
{
	t_command	*last;
	
	if (!*list)
		*list = new_cmd;
	else
	{
		last = *list;
		while (last->next)
			last = last->next;
		last->next = new_cmd;
	}
}

/* Adiciona argumento ao array args de um comando */
void	add_argument(t_command *cmd, char *arg)
{
	int		count;
	char	**new_args;
	
	// Contar argumentos atuais
	count = 0;
	if (cmd->args)
		while (cmd->args[count])
			count++;
	
	// Alocar novo array (+2: novo arg + NULL)
	new_args = (char **)ft_malloc((count + 2) * sizeof(char *));
	
	// Copiar argumentos antigos
	int i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	
	// Adicionar novo argumento
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	
	// Liberar array antigo e atualizar
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
}

/* Adiciona redirecionamento a um comando */
void	add_redirection(t_command *cmd, t_token *token)
{
	t_redir	*new_redir;
	t_redir	*last;
	
	// Criar novo redirecionamento
	new_redir = (t_redir *)ft_malloc(sizeof(t_redir));
	new_redir->type = token->type;
	new_redir->file = NULL;
	new_redir->fd = -1;
	new_redir->heredoc_fd = -1;
	new_redir->expanded = 0;
	new_redir->next = NULL;
	
	// Próximo token deve ser o arquivo/delimiter
	if (token->next && token->next->type == T_WORD)
	{
		// Para heredoc, NÃO expandir quotes agora
		// A expansão é feita no processamento do heredoc
		new_redir->file = ft_strdup(token->next->value);
		
		// Se for heredoc, marcar se delimiter tem quotes
		if (token->type == T_REDIR_HEREDOC)
		{
			// Se tem quotes, não expande variáveis
			if (ft_strchr(token->next->value, '\'') 
				|| ft_strchr(token->next->value, '"'))
				new_redir->expanded = 0;
			else
				new_redir->expanded = 1;
		}
	}
	
	// Adicionar à lista
	if (!cmd->redirs)
		cmd->redirs = new_redir;
	else
	{
		last = cmd->redirs;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
}

/* Verifica se é redirecionamento */
int	is_redirection(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT
		|| type == T_REDIR_APPEND || type == T_REDIR_HEREDOC);
}

/* Parser principal com expansão de quotes */
t_command	*parser(t_token *tokens, t_shell *shell)
{
	t_command	*cmd_list;
	t_command	*current_cmd;
	
	cmd_list = NULL;
	current_cmd = NULL;
	
	while (tokens && tokens->type != T_EOF)
	{
		// Novo comando se: primeiro comando ou encontrou pipe
		if (!current_cmd || tokens->type == T_PIPE)
		{
			if (tokens->type == T_PIPE)
				tokens = tokens->next;
			current_cmd = create_new_command();
			add_command(&cmd_list, current_cmd);
			if (!tokens || tokens->type == T_EOF)
				break;
		}
		
		// Redirecionamento
		if (is_redirection(tokens->type))
		{
			add_redirection(current_cmd, tokens);
			tokens = tokens->next; // Pula tipo
			if (tokens)
				tokens = tokens->next; // Pula arquivo
		}
		// Argumento normal
		else if (tokens->type == T_WORD)
		{
			add_argument(current_cmd, tokens->value);
			tokens = tokens->next;
		}
		// Pipe (já tratado acima)
		else
			tokens = tokens->next;
	}
	
	// PRIMEIRO: Expandir variáveis
	t_command *cmd = cmd_list;
	while (cmd)
	{
		expand_command_vars(cmd, shell);
		expand_redir_vars(cmd, shell);
		cmd = cmd->next;
	}
	
	/*
	// DEPOIS: Remover quotes
	cmd = cmd_list;
	while (cmd)
	{
		if (cmd->args)
			expand_command_args(cmd); // Sua função existente de remover quotes
		if (cmd->redirs)
			expand_redir_files(cmd);  // Sua função existente de remover quotes
		cmd = cmd->next;
	}*/
	
	return (cmd_list);
}
