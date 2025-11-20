/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:35:48 by ieusebio          #+#    #+#             */
/*   Updated: 2025/11/20 10:35:49 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

static void	draw_tile(t_game *game, int y, int x)
{
	char	tile = game->map[y][x];

	if (tile == '1')
		mlx_put_image_to_window(game->mlx_ptr, game->mlx_window,
			game->sprites.wall, x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == 'P')
	{
		mlx_put_image_to_window(game->mlx_ptr, game->mlx_window,
			game->sprites.player, x * TILE_SIZE, y * TILE_SIZE);
		game->player_x = x;
		game->player_y = y;
	}
	else if (tile == 'C')
		mlx_put_image_to_window(game->mlx_ptr, game->mlx_window,
			game->sprites.collectible, x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == '0')
		mlx_put_image_to_window(game->mlx_ptr, game->mlx_window,
			game->sprites.floor, x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == 'E')
		mlx_put_image_to_window(game->mlx_ptr, game->mlx_window,
			game->sprites.exit, x * TILE_SIZE, y * TILE_SIZE);
}

void	render_map(t_game *game)
{
	for (int y = 0; y < game->window_height; y++)
		for (int x = 0; x < game->window_width; x++)
			draw_tile(game, y, x);
}

