#include "../../include/so_long.h"

void flood_fill(char **map, int x, int y, int width, int height)
{
    if (x < 0 || y < 0 || x >= width || y >= height)
        return;
    if (map[y][x] == 'E')
    {
        map[y][x] = '1';
        return;
    }
    if (map[y][x] == '1' || map[y][x] == 'F')
        return;
    map[y][x] = 'F';
    flood_fill(map, x - 1, y, width, height);
    flood_fill(map, x + 1, y, width, height);
    flood_fill(map, x, y - 1, width, height);
    flood_fill(map, x, y + 1, width, height);
}

static int map_has_unreachable_items(char **map)
{
    int y;
    int x;

    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == 'C' || map[y][x] == 'E')
                return 0;
            x++;
        }
        y++;
    }
    return 1;
}


static void put_pos_player(t_game *game)
{
    int x;
    int y;

    y = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            if (game->map[y][x] == 'P')
            {
                game->player_x = x;
                game->player_y = y;
                return;
            }
            x++;
        }
        y++;
    }
}

static int is_playable(t_game *game)
{
    char **map_copy;
    int width;
    int height;

    width = ft_strlen(game->map[0]) - 1;
    height = get_quant_rows(game->map);
    map_copy = copy_map(game->map);
    if (!map_copy)
        return (0);
    put_pos_player(game);
    flood_fill(map_copy, game->player_x, game->player_y, width, height);
    if (!map_has_unreachable_items(map_copy))
    {
        free_buffer(map_copy);
        return (0);
    }
    free_buffer(map_copy);
    return (1);
}

void validation_map(t_game *game)
{
    if (!is_retangular(game->map))
        ft_show_error_with_free("Map Is not Retangular!", game->map);
    if (!has_allow_char(game->map))
        ft_show_error_with_free("Invalid Character!", game->map);
    if (!validade_quant_EPC(game->map))
        ft_show_error_with_free("Find Multiples values or Invalid colletions!", game->map);
    if (!check_walls(game->map))
        ft_show_error_with_free("Incorrect Walls!", game->map);
    if (!is_playable(game))
        ft_show_error_with_free("Game not Playable!", game->map);
}
