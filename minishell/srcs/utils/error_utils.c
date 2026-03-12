/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 17:19:07 by akudiezo          #+#    #+#             */
/*   Updated: 2026/02/12 17:19:26 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

/* Função para imprimir erros no formato do bash 
void	print_error(char *cmd, char *msg, int exit_code)
{
	(void)exit_code; // Será usado depois para setar $?
	
	write(2, "minishell: ", 11);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (msg)
		write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}*/

/* Função para imprimir erros no formato do bash */
void	print_error(char *cmd, char *msg, int exit_code)
{
	(void)exit_code;
	
	// Escrever "minishell: " uma única vez
	write(STDERR_FILENO, "minishell: ", 11);
	
	// Escrever o comando (se existir)
	if (cmd)
	{
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": ", 2);
	}
	
	// Escrever a mensagem de erro
	if (msg)
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, "\n", 1);
	}
	else
	{
		// Se não tem mensagem, usar strerror
		char *err_msg = strerror(errno);
		write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
		write(STDERR_FILENO, "\n", 1);
	}
}

/* Função específica para erro de comando não encontrado 
void	print_command_not_found(char *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
}*/

/* Função específica para erro de comando não encontrado */
void	print_command_not_found(char *cmd)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": command not found\n", 21);
}

/* Função para erro de permissão 
void	print_permission_denied(char *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": Permission denied\n", 21);
}*/

/* Função para erro de permissão */
void	print_permission_denied(char *cmd)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": Permission denied\n", 21);
}

/* Função para erro de diretório 
void	print_cd_error(char *path, char *msg)
{
	write(2, "minishell: cd: ", 15);
	if (path)
	{
		write(2, path, ft_strlen(path));
		write(2, ": ", 2);
	}
	if (msg)
		write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}*/

/* Função para erro de diretório */
void	print_cd_error(char *path, char *msg)
{
	write(STDERR_FILENO, "minishell: cd: ", 15);
	if (path)
	{
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, ": ", 2);
	}
	if (msg)
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, "\n", 1);
	}
}

/* Função genérica para erros com perror 
void	perror_msg(char *cmd)
{
	write(2, "minishell: ", 11);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	perror("");
}*/

/* Função genérica para erros com perror */
void	perror_msg(char *cmd)
{
	write(STDERR_FILENO, "minishell: ", 11);
	if (cmd)
	{
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": ", 2);
	}
	perror("");
}
