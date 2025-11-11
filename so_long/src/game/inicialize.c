#include "../../include/so_long.h"

void load_images(t_game *game)
{
    int img_width;
    int img_height;

    game->sprites.player = mlx_xpm_file_to_image(game->mlx_ptr, "textures/p.xpm", &img_width, &img_height);
    if (!game->sprites.player)
        ft_show_error("Load Failed Image Player!");
    game->sprites.exit = mlx_xpm_file_to_image(game->mlx_ptr, "textures/e.xpm", &img_width, &img_height);
    if (!game->sprites.exit)
        ft_show_error("Load Failed Image Exit!");    
    game->sprites.wall = mlx_xpm_file_to_image(game->mlx_ptr, "textures/1.xpm", &img_width, &img_height);
    if (!game->sprites.wall)
        ft_show_error("Load Failed Image Wall!");
    game->sprites.floor = mlx_xpm_file_to_image(game->mlx_ptr, "textures/0.xpm", &img_width, &img_height);
    if (!game->sprites.floor)
        ft_show_error("Load Failed Image Floor!");
    game->sprites.collectible = mlx_xpm_file_to_image(game->mlx_ptr, "textures/c.xpm", &img_width, &img_height);
    if (!game->sprites.floor)
        ft_show_error("Load Failed Image Collectible!");
}

void inicialize_game(t_game *game)
{
    game->window_width = ft_strlen(game->map[0]) - 1;
    game->window_height = get_quant_rows();
    game->count_move = 0;

    game->mlx_ptr = mlx_init();
    if (!game->mlx_ptr)
        ft_show_error("mlx init filed");

    game->mlx_window = mlx_new_window(game->mlx_ptr, game->window_width * TILE_SIZE, game->window_height * TILE_SIZE, "Thank you Jesus!");
    if (!game->mlx_window)
        ft_show_error("mlx window filed");

    load_images(game);
}