#include "../../include/so_long.h"

int get_quant_rows()
{
    char *line_read;
    int fd;
    int quant_rows;

    line_read = NULL;
    fd = ft_open_file(SOURCE_MAP);
    quant_rows = 0;
    while ((line_read = get_next_line(fd)))
    {   
        quant_rows++;
        free(line_read);
        line_read = NULL;
    }
    close(fd);
    return (quant_rows);
}


int is_retangular()
{
    int len_line;
    char *line_read;
    int first_loop;
    int fd;

    first_loop = 0;
    line_read = NULL;
    fd = ft_open_file(SOURCE_MAP);
    while ((line_read = get_next_line(fd)))
    {
        if (!first_loop)
        {
            len_line = ft_strlen_without_break(line_read);
            first_loop = 1;
        }
        if (ft_strlen_without_break(line_read) != len_line)
        {
            close(fd);
            free(line_read);
            return (0);
        }
        free(line_read);
        line_read = NULL;
    }
    if (!first_loop && !line_read)
    {
        close(fd);
        return (0);
    }
    close(fd);
    return (1);
}

int has_allow_char()
{
    int i;
    char *line_read;
    int fd;

    line_read = NULL;
    fd = ft_open_file(SOURCE_MAP);
    while ((line_read = get_next_line(fd)))
    {
        i = 0;
        while (line_read[i] && line_read[i] != '\n')
        {
            if (line_read[i] != '0' && line_read[i] != '1' && line_read[i] != 'C' && line_read[i] != 'E' && line_read[i] != 'P')
            {
                close(fd);
                free(line_read);
                return (0);
            }
            i++;
        }
        free(line_read);
        line_read = NULL;
    }
    close(fd);
    return (1);
}

int validade_quant_EPC()
{
    char *line_read;
    int cont_E;
    int cont_P;
    int cont_C;
    int fd;

    cont_E = 0;
    cont_P = 0;
    cont_C = 0;
    line_read = NULL;
    fd = ft_open_file(SOURCE_MAP);
    while ((line_read = get_next_line(fd)))
    {
        cont_E += ft_occur(line_read, 'E');
        cont_P += ft_occur(line_read, 'P');
        cont_C += ft_occur(line_read, 'C');
        free(line_read);
        line_read = NULL;
    }
    if (cont_E != 1 || cont_P != 1 || cont_C < 1)
    {
        close(fd);
        return (0);
    }
    close(fd);
    return (1);
}

int check_walls(char **lines_buffer)
{
    int i;
    int k;
    int rows;
    int pos_break_line;

    rows = get_quant_rows();
    i = 0;
    while (lines_buffer[i])
    {
        k = 0;
        if (i == 0)
        {
            while (lines_buffer[i][k] && lines_buffer[i][k] != '\n')
            {
                if (lines_buffer[i][k] != '1')
                    return (0);
                k++;
            }
        }
        else if (i > 0 && i < rows - 1)
        {
            pos_break_line = ft_strchr(lines_buffer[i], '\n');
            if (lines_buffer[i][0] != '1' || lines_buffer[i][pos_break_line - 1] != '1')
                return (0);
        }
        else
        {
            while (lines_buffer[i][k])
            {
                if (lines_buffer[i][k] != '1')
                    return (0);
                k++;
            }
        }
        i++;
    }
    return (1);
}

int is_sorrounded_walls()
{
    char *line_read;
    char **lines_buffer;
    int fd;
    int i;
    int rows;

    line_read = NULL;
    fd = ft_open_file(SOURCE_MAP);

    i = 0;
    rows = get_quant_rows();
    lines_buffer = (char **)malloc((rows + 1) * sizeof(char *));
    if (!lines_buffer)
    {
        close(fd);
        return (0);
    }
    while ((line_read = get_next_line(fd)))
    {
        lines_buffer[i] = ft_strdup(line_read);
        if (!lines_buffer[i])
        {
            close(fd);
            return (0);
        }
        i++;
        free(line_read);
        line_read = NULL;
    }
    lines_buffer[i] = NULL;
    if (!check_walls(lines_buffer))
    {
        free_buffer(lines_buffer);
        close(fd);
        return (0);
    }

    free_buffer(lines_buffer);
    close(fd);
    return (1);
}