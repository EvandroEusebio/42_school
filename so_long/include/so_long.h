#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <stddef.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

typedef struct s_game
{
    char **map;
    void *mlx_ptr;
    void *mlx_window;
    int window_width;
    int window_height;
} t_game;

void inicialize_game(t_game *game);
char	*get_next_line(int fd);
void store_map(t_game *game);
char *ft_strcopy(char *dest, const char *src);
char	*ft_strcopy_limit(const char *str, int limit);
int	ft_strlen_without_break(const char *str);
void ft_show_error(char *message);
void ft_show_error_with_free(char *message, char *var_to_free);
int ft_occur(char *str, char c);
void validation_map();
int ft_open_file(char *source);
int get_quant_rows();
char	*ft_strdup(const char *s);
void free_buffer(char **buffer);
int is_retangular();
int has_allow_char();
int validade_quant_EPC();
int check_walls(char **lines_buffer);
char	*ft_join(char *str1, char *str2);
int is_sorrounded_walls();

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef TILE_SIZE
#  define TILE_SIZE 64
# endif


# ifndef SOURCE_MAP
#  define SOURCE_MAP "maps/map.ber"
# endif

#endif