/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:26:12 by ieusebio          #+#    #+#             */
/*   Updated: 2025/11/20 10:26:15 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	game_over(t_game *game)
{
	ft_printf("================\n");
	ft_printf("    WINNER      \n");
	ft_printf("================\n");
	quit_game(game);
}

int	quit_game(t_game *game)
{
	if (game->mlx_ptr && game->mlx_window)
		mlx_destroy_window(game->mlx_ptr, game->mlx_window);
	if (game->mlx_ptr && game->sprites.wall)
		mlx_destroy_image(game->mlx_ptr, game->sprites.wall);
	if (game->mlx_ptr && game->sprites.floor)
		mlx_destroy_image(game->mlx_ptr, game->sprites.floor);
	if (game->mlx_ptr && game->sprites.player)
		mlx_destroy_image(game->mlx_ptr, game->sprites.player);
	if (game->mlx_ptr && game->sprites.collectible)
		mlx_destroy_image(game->mlx_ptr, game->sprites.collectible);
	if (game->mlx_ptr && game->sprites.exit)
		mlx_destroy_image(game->mlx_ptr, game->sprites.exit);
	if (game->mlx_ptr)
		mlx_destroy_display(game->mlx_ptr);
	if (game->map)
		free_buffer(game->map);
	free(game->mlx_ptr);
	exit(1);
}
