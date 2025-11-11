#include "../../include/so_long.h"

void game_over(t_game *game)
{
    printf("GAME OVER\n");
    close_window(game);
}

void close_window(t_game *game)
{
    mlx_destroy_window(game->mlx_ptr, game->mlx_window);
    mlx_destroy_image(game->mlx_ptr, game->sprites.wall);
    mlx_destroy_image(game->mlx_ptr, game->sprites.floor);
    mlx_destroy_image(game->mlx_ptr, game->sprites.player);
    mlx_destroy_image(game->mlx_ptr, game->sprites.collectible);
    mlx_destroy_image(game->mlx_ptr, game->sprites.exit);
    mlx_destroy_display(game->mlx_ptr);
    free_buffer(game->map);
    free(game);
    exit(0);
}

