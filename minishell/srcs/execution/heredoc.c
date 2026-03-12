/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 16:21:36 by akudiezo          #+#    #+#             */
/*   Updated: 2026/02/12 16:23:21 by akudiezo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h" 	

/* Versão simplificada de expand_variables APENAS para o heredoc */
/*static char	*expand_heredoc_line(char *line, t_shell *shell)
{
	char	*result;
	char	*temp;
	char	var_name[256];
	int		i;
	int		j;
	char	*value;
	
	if (!line)
		return (NULL);
	
	result = ft_strdup("");
	i = 0;
	
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && 
			(ft_isalnum(line[i + 1]) || line[i + 1] == '_' || line[i + 1] == '?'))
		{
			i++; // Pular $
			
			// $?
			if (line[i] == '?')
			{
				value = ft_itoa(shell->exit_status);
				temp = ft_strjoin(result, value);
				free(result);
				free(value);
				result = temp;
				i++;
				continue;
			}
			
			// Coletar nome da variável
			j = 0;
			while (line[i] && (ft_isalnum(line[i]) || line[i] == '_') && j < 255)
				var_name[j++] = line[i++];
			var_name[j] = '\0';
			
			// Buscar valor
			value = get_env_value(var_name, shell);
			if (!value)
				value = ft_strdup("");
			
			temp = ft_strjoin(result, value);
			free(result);
			free(value);
			result = temp;
		}
		else
		{
			// Caractere normal
			char tmp[2] = {line[i], '\0'};
			temp = ft_strjoin(result, tmp);
			free(result);
			result = temp;
			i++;
		}
	}
	
	return (result);
}*/

/* Limpa o buffer do stdin */
/*
static void	clear_stdin(void)
{
	int	c;
	
	// Ler e descartar todos os caracteres pendentes no stdin
	while ((c = getchar()) != '\n' && c != EOF)
		;
}*/

/* Limpa o buffer do stdin usando termios */
/*static void	clear_input_buffer(void)
{
	struct termios	term;
	
	// Desabilitar ICANON para ler caracteres individuais
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	
	// Ler e descartar todos os caracteres disponíveis
	char buffer[256];
	while (read(STDIN_FILENO, buffer, sizeof(buffer)) > 0)
		;
	
	// Restaurar configurações originais
	term.c_lflag |= ICANON;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}*/

/* Versão para heredoc com suporte a escapes */
static char	*expand_heredoc_line(char *line, t_shell *shell)
{
	char	*result;
	char	*temp;
	char	var_name[256];
	int		i;
	int		j;
	int		escape_next;
	char	*value;
	char	tmp[2];
	
	if (!line)
		return (NULL);
	
	result = ft_strdup("");
	i = 0;
	escape_next = 0;
	
	while (line[i])
	{
		// Tratar escape character
		if (line[i] == '\\' && !escape_next)
		{
			// No heredoc, backslash escapa o próximo caractere
			if (line[i + 1])
			{
				i++; // Pular o backslash
				tmp[0] = line[i];
				tmp[1] = '\0';
				temp = ft_strjoin(result, tmp);
				free(result);
				result = temp;
				i++;
				continue;
			}
		}
		
		// Verificar se é $ para expandir (e não está escapado)
		if (line[i] == '$' && !escape_next && line[i + 1] && 
			(ft_isalnum(line[i + 1]) || line[i + 1] == '_' || line[i + 1] == '?'))
		{
			i++; // Pular $
			
			// $?
			if (line[i] == '?')
			{
				value = ft_itoa(shell->exit_status);
				temp = ft_strjoin(result, value);
				free(result);
				free(value);
				result = temp;
				i++;
				continue;
			}
			
			// Coletar nome da variável
			j = 0;
			while (line[i] && (ft_isalnum(line[i]) || line[i] == '_') && j < 255)
				var_name[j++] = line[i++];
			var_name[j] = '\0';
			
			// Buscar valor
			value = get_env_value(var_name, shell);
			if (!value)
				value = ft_strdup("");
			
			temp = ft_strjoin(result, value);
			free(result);
			free(value);
			result = temp;
		}
		else
		{
			// Caractere normal
			tmp[0] = line[i];
			tmp[1] = '\0';
			temp = ft_strjoin(result, tmp);
			free(result);
			result = temp;
			i++;
		}
		
		escape_next = 0;
	}
	
	return (result);
}

/* Lê e descarta linhas do heredoc (usado quando não há comando) */
void	read_heredoc_discard(char *delimiter, int expand, t_shell *shell)
{
	char	*line;
	char	*expanded_line;

	if (!delimiter)
		return;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(STDERR_FILENO, "\n", 1);
			break;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		if (expand)
		{
			expanded_line = expand_heredoc_line(line, shell);
			free(expanded_line);
		}
		free(line);
	}
}

/* Escreve o heredoc no pipe (executado no filho) */
static void	write_heredoc(int write_fd, char *delimiter, int expand, t_shell *shell)
{
	char	*line;
	char	*expanded_line;

	if (!delimiter)
		exit(1);

	// O filho deve tratar sinais normalmente
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	while (1)
	{
		line = readline("> ");
		if (!line) // Ctrl+D
		{
			write(STDERR_FILENO, "\n", 1);
			break;
		}

		// Comparar com o delimitador (linha original, sem expansão)
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}

		if (expand)
		{
			expanded_line = expand_heredoc_line(line, shell);
			if (expanded_line)
			{
				write(write_fd, expanded_line, ft_strlen(expanded_line));
				write(write_fd, "\n", 1);
				free(expanded_line);
			}
		}
		else
		{
			write(write_fd, line, ft_strlen(line));
			write(write_fd, "\n", 1);
		}
		free(line);
	}
	close(write_fd);
	exit(0);
}

/* Processa heredoc: cria pipe e fork, com restauração do terminal */
int	process_heredoc(char *delimiter, int expand, t_shell *shell)
{
	int			pipe_fd[2];
	pid_t		pid;
	int			status;
	struct termios	orig;

	if (!delimiter)
		return (-1);

	// Salva configurações atuais do terminal
	tcgetattr(STDIN_FILENO, &orig);

	// Cria pipe
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}

	if (pid == 0) // Filho
	{
		close(pipe_fd[0]);
		write_heredoc(pipe_fd[1], delimiter, expand, shell);
		// nunca chega aqui
	}
	else // Pai
	{
		close(pipe_fd[1]);
		signal(SIGINT, SIG_IGN); // ignora Ctrl+C durante o heredoc

		waitpid(pid, &status, 0);

		// RESTAURA O TERMINAL
		tcsetattr(STDIN_FILENO, TCSANOW, &orig);
		// Limpa qualquer dado residual no buffer de entrada
		tcflush(STDIN_FILENO, TCIFLUSH);

		// Reconfigura sinais do shell
		setup_signals();

		if (WIFSIGNALED(status))
		{
			close(pipe_fd[0]);
			return (-1);
		}
		return (pipe_fd[0]);
	}
	return (-1);
}

/* Verifica se delimiter deve expandir variáveis */
/*int	should_expand_delimiter(char *delimiter)
{
	if (!delimiter)
		return (0);
	
	// Se delimiter tem quotes, NÃO expande
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'))
		return (0);
	
	return (1);
}*/

/* Verifica se delimiter deve expandir variáveis */
int	should_expand_delimiter(char *delimiter)
{
	if (!delimiter)
		return (0);
	return (!(ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"')));
}

/* Limpa delimiter: remove quotes se houver */
char	*clean_delimiter(char *delimiter)
{
	char	*cleaned;
	
	if (!delimiter)
		return (NULL);
	
	// Se tem quotes, remove
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'))
		cleaned = remove_quotes(delimiter);
	else
		cleaned = ft_strdup(delimiter);
	
	return (cleaned);
}
