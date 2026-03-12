/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:55:19 by akudiezo          #+#    #+#             */
/*   Updated: 2026/01/27 17:08:38 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/* Função para debug (remover depois) */
void print_debug_info(t_token *tokens, t_command *cmd)
{
	printf("\n=== DEBUG INFO ===\n");
	
	// Print tokens
	printf("Tokens:\n");
	t_token *t = tokens;
	while (t)
	{
		printf("  [%s] type: %d\n", t->value, t->type);
		t = t->next;
	}
	
	// Print commands
	printf("\nCommands:\n");
	t_command *c = cmd;
	int cmd_num = 0;
	while (c)
	{
		printf("  Command %d:\n", cmd_num++);
		printf("    Args: ");
		int i = 0;
		while (c->args && c->args[i])
		{
			printf("[%s] ", c->args[i]);
			i++;
		}
		printf("\n");
		c = c->next;
	}
	printf("==================\n\n");
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	
	(void)argc;
	(void)argv;
	
	// Inicialização
	init_shell(&shell, env);
	init_env_list(&shell, env);
	
	// Loop principal
	while (1)
	{
		// Configurar sinais
		setup_signals();
		
		// Ler input
		shell.line = readline("minishell> ");
		if (!shell.line) // Ctrl+D
		{
			printf("exit\n");
			break;
		}
		
		// Se linha não vazia, processar
		if (ft_strlen(shell.line) > 0)
		{
			//Verificar quotes não fechadas
			if (has_unclosed_quotes(shell.line))
			{
				quote_error();
				free(shell.line);
				shell.exit_status = 1;
				continue;
			}
		
			add_history(shell.line);
			
			// 1. Tokenização
			t_token *tokens = tokenizer(shell.line);
			
			// 2. Verificar sintaxe
			if (syntax_check(tokens) == 0)
			{
				// 3. Parsing
				shell.cmd_list = parser(tokens, &shell);
				
				// DEBUG: mostrar tokens e comandos
				//print_debug_info(tokens, shell.cmd_list);
				
				// 4. Execução
				if (shell.cmd_list)
					executor(&shell);
				
				// 5. Limpar comandos
				cleanup_commands(shell.cmd_list);
				shell.cmd_list = NULL;
			}
			
			// Limpar tokens
			cleanup_tokens(tokens);
		}
		free(shell.line);
		shell.line = NULL;
	}
	
	// Limpeza final
	cleanup_shell(&shell);
	free_env_list(shell.env_list);
	return (shell.exit_status);
}
