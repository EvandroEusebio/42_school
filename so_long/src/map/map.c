#include "../../include/so_long.h"

void store_map(t_game *game)
{
    char *line_read;
    int fd;
    int i;
    int rows;

    fd = ft_open_file(SOURCE_MAP);

    i = 0;
    rows = get_quant_rows();
    game->map = (char **)malloc((rows + 1) * sizeof(char *));
    if (!game->map)
    {
        close(fd);
        ft_show_error("BAD allocation  2D Map");
    }
    while ((line_read = get_next_line(fd)))
    {
        game->map[i] = ft_strdup(line_read);
        if (!game->map[i])
        {
            close(fd);
            ft_show_error("Error Store 2D Map");
        }
        i++;
        free(line_read);
        line_read = NULL;
    }
    game->map[i] = NULL;
    close(fd);
}

void inicialize_game(t_game *game)
{
    game->window_width = (ft_strlen(game->map[0]) - 1) * TILE_SIZE;
    game->window_height = get_quant_rows() * TILE_SIZE;

    game->mlx_ptr = mlx_init();
    if (!game->mlx_ptr)
        ft_show_error("mlx init filed");

    game->mlx_window = mlx_new_window(game->mlx_ptr, game->window_width, game->window_height, "Thank you Jesus!");
    if (!game->mlx_window)
        ft_show_error("mlx window filed");

    mlx_loop(game->mlx_ptr);
}
