/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ieusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:13:59 by ieusebio          #+#    #+#             */
/*   Updated: 2025/11/20 10:14:00 by ieusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	run_game(char **arguments)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	read_store_map(&game, arguments[1]);
	validation_map(&game);
	inicialize_game(&game);
	render_map(&game);
	mlx_hook(game.mlx_window, MLX_KEY_PRESS, 1L << 0, &key_press, &game);
	mlx_hook(game.mlx_window, MLX_CLOSE, 1L << 17, &quit_game, &game);
	mlx_loop(game.mlx_ptr);
}

int	main(int quant_arg, char **arg)
{
	if (quant_arg != 2)
		ft_show_error("Invalid Arguments Number!");
	check_file_name(arg[1]);
	run_game(arg);
	return (0);
}
