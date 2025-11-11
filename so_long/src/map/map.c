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

int existType(char **map, char c)
{
    int x;
    int y;

    x = 0;
    while(map[x])
    {
        y = 0;
        while(map[x][y])
        {
            if(map[x][y] == c)
                return (1);
            y++;
        }
        x++;
    }
    return (0);
}


