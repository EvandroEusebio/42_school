#include "../../include/so_long.h"

void render_map(t_game *game)
{
    int y;
    int x;

    y = 0;
    while (y < game->window_height)
    {
        x = 0;
        while (x < game->window_width)
        {
            if (game->map[y][x] == '1')
                mlx_put_image_to_window(game->mlx_ptr, game->mlx_window, game->sprites.wall, x * TILE_SIZE, y * TILE_SIZE);
            if (game->map[y][x] == 'P')
            {
                mlx_put_image_to_window(game->mlx_ptr, game->mlx_window, game->sprites.player, x * TILE_SIZE, y * TILE_SIZE);
                game->player_x = x;
                game->player_y = y;
            }
            if (game->map[y][x] == 'C')
                mlx_put_image_to_window(game->mlx_ptr, game->mlx_window, game->sprites.collectible, x * TILE_SIZE, y * TILE_SIZE);
            if (game->map[y][x] == '0')
                mlx_put_image_to_window(game->mlx_ptr, game->mlx_window, game->sprites.floor, x * TILE_SIZE, y * TILE_SIZE);
            if (game->map[y][x] == 'E')
                mlx_put_image_to_window(game->mlx_ptr, game->mlx_window, game->sprites.exit, x * TILE_SIZE, y * TILE_SIZE);
            x++;
        }
        y++;
    }
}