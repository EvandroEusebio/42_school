/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 18:40:01 by akudiezo          #+#    #+#             */
/*   Updated: 2026/02/20 18:41:07 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

/* Inicializa a lista de ambiente a partir do envp */
void	init_env_list(t_shell *shell, char **env)
{
	int		i;
	char	*equal_sign;
	char	*key;
	char	*value;
	t_list	*new_node;
	
	shell->env_list = NULL;
	i = 0;
	while (env[i])
	{
		// Separar KEY=value
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign)
		{
			key = ft_substr(env[i], 0, equal_sign - env[i]);
			value = ft_strdup(equal_sign + 1);
			
			// Guardar como "KEY=value" na lista
			char *entry = ft_strjoin(key, "=");
			char *full_entry = ft_strjoin(entry, value);
			
			new_node = ft_lstnew(full_entry);
			ft_lstadd_back(&shell->env_list, new_node);
			
			free(key);
			free(value);
			free(entry);
		}
		else
		{
			// Variável sem valor (ex: apenas KEY)
			new_node = ft_lstnew(ft_strdup(env[i]));
			ft_lstadd_back(&shell->env_list, new_node);
		}
		i++;
	}
}

/* Busca valor de uma variável no ambiente */
char	*get_env_value(char *var_name, t_shell *shell)
{
	t_list	*current;
	char	*entry;
	char	*equal_sign;
	char	*key;
	char	*value;
	
	if (!var_name || !shell || !shell->env_list)
		return (NULL);
	
	// Caso especial: $? (exit status)
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(shell->exit_status));
	
	current = shell->env_list;
	while (current)
	{
		entry = (char *)current->content;
		equal_sign = ft_strchr(entry, '=');
		if (equal_sign)
		{
			key = ft_substr(entry, 0, equal_sign - entry);
			if (key && ft_strcmp(key, var_name) == 0)
			{
				value = ft_strdup(equal_sign + 1);
				free(key);
				return (value);
			}
			if (key)
				free(key);
		}
		current = current->next;
	}
	
	// Não encontrou - retorna string vazia (comportamento do bash)
	return (ft_strdup(""));
}

/* Libera a lista de ambiente */
void	free_env_list(t_list *env_list)
{
	ft_lstclear(&env_list, free);
}

/* Atualiza o array env (para execve) a partir da lista */
char	**update_env_array(t_shell *shell)
{
	char	**new_env;
	t_list	*current;
	int		i;
	
	if (!shell->env_list)
		return (NULL);
	
	new_env = malloc(sizeof(char *) * (ft_lstsize(shell->env_list) + 1));
	if (!new_env)
		return (NULL);
	
	current = shell->env_list;
	i = 0;
	while (current)
	{
		new_env[i] = ft_strdup((char *)current->content);
		current = current->next;
		i++;
	}
	new_env[i] = NULL;
	
	// Liberar array antigo
	if (shell->env)
		free_array(shell->env);
	
	return (new_env);
}

/*
 * Altera ou cria uma variável de ambiente na lista. Se value for NULL,
 * adiciona/atualiza a variável com string vazia (KEY=).
 * Após modificar a lista, atualiza também shell->env (array) chamando
 * update_env_array.
 */
void	set_env_value(t_shell *shell, char *key, char *value)
{
	t_list *current;
	char *entry;
	char *new_entry;

	if (!shell || !key)
		return;
	if (value)
		new_entry = ft_strjoin3(key, "=", value);
	else
		new_entry = ft_strjoin(key, "=");
	current = shell->env_list;
	while (current)
	{
		entry = (char *)current->content;
		if (entry && ft_strncmp(entry, key, ft_strlen(key)) == 0
			&& (entry[ft_strlen(key)] == '=' || entry[ft_strlen(key)] == '\0'))
		{
			free(current->content);
			current->content = new_entry;
			shell->env = update_env_array(shell);
			return;
		}
		current = current->next;
	}
	/* não encontrou: adicionar no fim */
	current = ft_lstnew(new_entry);
	ft_lstadd_back(&shell->env_list, current);
	shell->env = update_env_array(shell);
}

/*
 * Remove variável da lista de ambiente se existir. Atualiza o array.
 */
void	unset_env_value(t_shell *shell, char *key)
{
	t_list *current;
	t_list *prev;
	char *entry;

	if (!shell || !key)
		return;
	prev = NULL;
	current = shell->env_list;
	while (current)
	{
		entry = (char *)current->content;
		if (entry && ft_strncmp(entry, key, ft_strlen(key)) == 0
			&& (entry[ft_strlen(key)] == '=' || entry[ft_strlen(key)] == '\0'))
		{
			if (prev)
				prev->next = current->next;
			else
				shell->env_list = current->next;
			free(current->content);
			free(current);
			shell->env = update_env_array(shell);
			return;
		}
		prev = current;
		current = current->next;
	}
}
