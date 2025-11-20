/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_name_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:21:20 by ieusebio          #+#    #+#             */
/*   Updated: 2025/11/20 10:21:22 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	check_file_name(char *file_name)
{
	char	*file;

	file = file_name + ft_strchr(file_name, '/') + 1;
	if (!ft_strnstr(file, ".ber", ft_strlen(file_name)))
		ft_show_error("Incorrect file Name!");
	if (!ft_strncmp(file, ".ber", ft_strlen(file)))
		ft_show_error("Incorrect file name .ber");
}

int	ft_open_file(char *source)
{
	int	fd;

	fd = open(source, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nOpen File!");
		exit(1);
	}
	return (fd);
}
