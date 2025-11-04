#include "../include/so_long.h"



int main()
{
    t_game game;
    // validation & read map
    validation_map();
    // Store map
    store_map(&game);

    //inicialize game window 
    


    free_buffer(game.map);
    
    return (0);
}