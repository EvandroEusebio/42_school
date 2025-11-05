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

void render_map(t_game *game)
{
    int y;
    int x;

    y = 0;
    x = 0;
    while (y < game->window_height)
    {
        x = 0;
        while (x < game->window_width)
        {
            if (game->map[y][x] == '1')
                mlx_put_image_to_window(game->mlx_ptr, game->mlx_window, game->sprites.wall, x * TILE_SIZE, y * TILE_SIZE);
            if (game->map[y][x] == 'P')
                mlx_put_image_to_window(game->mlx_ptr, game->mlx_window, game->sprites.player, x * TILE_SIZE, y * TILE_SIZE);
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
