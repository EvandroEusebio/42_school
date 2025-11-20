#include "../../include/so_long.h"

static int quant_rows_file(char *source)
{    
    char *line_read;
    int fd;
    int quant_rows;

    fd = ft_open_file(source);
    quant_rows = 0;
    while ((line_read = get_next_line(fd)))
    {
        quant_rows++;
        free(line_read);
        line_read = NULL;
    }
    return (quant_rows);
}

static char **create_map(int rows, int fd)
{
    char **temp_map;

    temp_map = (char **)malloc((rows + 1) * sizeof(char *));
    if (!temp_map)
    {
        close(fd);
        ft_show_error("BAD allocation 2D Map");
    }
    return (temp_map);
}

void read_store_map(t_game *game, char *source)
{
    char *line_read;
    int fd;
    int i;
    int rows;

    fd = ft_open_file(source);
    i = 0;
    rows = quant_rows_file(source);
    game->map = create_map(rows, fd);
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

char **copy_map(char **original_map)
{
    char **map_copy;
    int i;

    if (!original_map)
        return (NULL);
    map_copy = malloc((get_quant_rows(original_map) + 1) * sizeof(char *));
    if (!map_copy)
        return (NULL);
    i = 0;
    while (original_map[i])
    {
        map_copy[i] = ft_strdup(original_map[i]);
        i++;
    }
    map_copy[i] = NULL;
    return (map_copy);
}


