#include "../include/so_long.h"

int main()
{
    t_game *game;
    // init_pointer
    game = malloc(sizeof(t_game));
    if (!game)
    {
        perror("Failed to allocate memory for game");
        return (1);
    }

    // validation & read map
    validation_map();
    // Store map
    store_map(game);
    // inicialize game window
    inicialize_game(game);
    // draw components
    render_map(game);

    mlx_loop(game->mlx_ptr);

    mlx_destroy_image(game->mlx_ptr, game->sprites.player);
    mlx_destroy_image(game->mlx_ptr, game->sprites.collectible);
    mlx_destroy_image(game->mlx_ptr, game->sprites.floor);
    mlx_destroy_image(game->mlx_ptr, game->sprites.wall);
    mlx_destroy_image(game->mlx_ptr, game->sprites.exit);

    free_buffer(game->map);

    return (0);
}