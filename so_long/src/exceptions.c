/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:12:26 by ieusebio          #+#    #+#             */
/*   Updated: 2025/11/20 10:12:28 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	ft_show_error(char *message)
{
	ft_printf("ERROR\n%s", message);
	exit(1);
}

void	ft_show_error_all(char *message, t_game *game)
{
	ft_printf("ERROR\n%s", message);
	quit_game(game);
}

void	ft_show_error_with_free(char *message, char **buffer)
{
	ft_printf("ERROR\n%s", message);
	free_buffer(buffer);
	exit(1);
}

void	free_buffer(char **buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		free(buffer[i]);
		i++;
	}
	free(buffer);
}
