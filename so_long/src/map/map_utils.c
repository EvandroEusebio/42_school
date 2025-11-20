#include "../../include/so_long.h"

int get_quant_rows(char **map)
{    
    int quant_rows;
    int i;

    quant_rows = 0;
    i = 0;
    while (map[i])
    {   
        quant_rows++;
        i++;
    }
    return (quant_rows);
}


int is_retangular(char **map)
{
    int i;
    int ref_len;

    if (!map || !map[0]) 
        return (0);
    ref_len = ft_strlen_without_break(map[0]);
    i = 1;
    while (map[i])
    {
        if (ft_strlen_without_break(map[i]) != ref_len)
            return (0);
        i++;
    }
    return (1);
}

int has_allow_char(char **map)
{
    int i;
    int k;

    i = 0;
    while (map[i])
    {
        k = 0;
        while (map[i][k] && map[i][k] != '\n')
        {
            if (map[i][k] != '0' && map[i][k] != '1' && map[i][k] != 'C'
                && map[i][k] != 'E' && map[i][k] != 'P')
                return (0);
            k++;
        }
        i++;
    }
    return (1);
}

int validade_quant_EPC(char **map)
{
    int cont_E;
    int cont_P;
    int cont_C;
    int i;

    cont_E = 0;
    cont_P = 0;
    cont_C = 0;
    i = 0;
    while (map[i])
    {
        cont_E += ft_occur(map[i], 'E');
        cont_P += ft_occur(map[i], 'P');
        cont_C += ft_occur(map[i], 'C');
        i++;
    }
    if (cont_E != 1 || cont_P != 1 || cont_C < 1)
        return (0);
    return (1);
}

int check_walls(char **map)
{
    int y;
    int x;
    int rows;
    int cols;

    rows = get_quant_rows(map);
    cols = ft_strlen_without_break(map[0]);
    y = -1;
    while(++y < rows)
    {
        if (map[y][0] != '1' || map[y][cols - 1] != '1')
            return (0);
    }
    x = -1;
    while(++x < cols)
    {
        if (map[0][x] != '1' || map[rows - 1][x] != '1')
            return (0);
    }
    return (1);
}
