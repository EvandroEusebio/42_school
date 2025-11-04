
#include "../include/so_long.h"

static char	*ft_read_file(int fd, char *container_text)
{
	char	*buffer;
	int		n_bytes_read;

	n_bytes_read = 1;
	while (n_bytes_read > 0 && ft_strchr(container_text, 10) == -1)
	{
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (NULL);
		n_bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (n_bytes_read <= 0 && (!container_text || container_text[0] == '\0'))
		{
			free(buffer);
			break ;
		}
		buffer[n_bytes_read] = 0;
		container_text = ft_join(container_text, buffer);


		free(buffer);
	}
	return (container_text);
}

static char	*ft_get_line(char **container_text)
{
	char	*temp;
	char	*line;
	int		pos_break_line;

	pos_break_line = ft_strchr(*container_text, 10);
	line = NULL;
	if (pos_break_line > -1)
	{
		line = ft_strcopy_limit(*container_text, pos_break_line);
		temp = ft_join(NULL, *container_text + pos_break_line + 1);
		free(*container_text);
		*container_text = temp;
	}
	else
	{
		line = ft_join(line, *container_text);
		free(*container_text);
		*container_text = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest = ft_read_file(fd, rest);
	if (!rest || rest[0] == '\0')
	{
		free(rest);
		return (NULL);
	}
	line = ft_get_line(&rest);
	if (rest && *rest == 0)
	{
		free(rest);
		rest = NULL;
	}
	return (line);
}
