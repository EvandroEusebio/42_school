#include "../../include/so_long.h"

static void move(t_game *game, int dx, int dy)
{
    int new_x;
    int new_y;
    new_x = game->player_x + dx;
    new_y = game->player_y + dy;

    // adde order verify
    if (game->map[new_y][new_x] == '1')
        return ;
    if (game->map[new_y][new_x] == 'E' && existType(game->map, 'C'))
        return ;
    
    game->map[game->player_y][game->player_x] = '0';
    game->map[new_y][new_x] = 'P';
    render_map(game);
    game->count_move++;
    printf("Quant Move: %d\n", game->count_move);
}

void move_player(char type_moviment, t_game *game)
{
    if (type_moviment == 'U')
        move(game, 0, -1);
    if (type_moviment == 'D')
        move(game, 0, 1);
    if (type_moviment == 'L')
        move(game, -1, 0);
    if (type_moviment == 'R')
        move(game, 1, 0);
}

int close_game(t_game *game)
{
    mlx_destroy_window(game->mlx_ptr, game->mlx_window);
    exit(0);
    return (0);
}

int key_press(int keycode, t_game *game)
{
    if (keycode == KEYPRESS_A)
        move_player('L', game);
    if (keycode == KEYPRESS_W)
        move_player('U', game);
    if (keycode == KEYPRESS_D)
        move_player('R', game);
    if (keycode == KEYPRESS_S)
        move_player('D', game);
    if (keycode == ESC)
        close_game(game);
    return (0);
}