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

    free_buffer(game->map);

    return (0);
}