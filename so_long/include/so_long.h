#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <stddef.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

typedef struct s_sprites
{
    void *wall;
    void *floor;
    void *player;
    void *exit;
    void *collectible;
}   t_sprites;


typedef struct s_game
{
    char **map;
    void *mlx_ptr;
    void *mlx_window;
    int window_width;
    int window_height;
    t_sprites sprites;
    int player_x;
    int player_y;
    int count_move;
} t_game;


void move_player(char type_moviment, t_game *game);
int close_game(t_game *game);
int key_press(int keycode, t_game *game);
void render_map(t_game *game);
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
void free_buffer(char **buffer);
int is_retangular();
int has_allow_char();
int validade_quant_EPC();
int check_walls(char **lines_buffer);
char	*ft_join(char *str1, char *str2);
int is_sorrounded_walls();
int existType(char **map, char c);


#  define BUFFER_SIZE 42
#  define TILE_SIZE 32
#  define SOURCE_MAP "maps/map.ber"

# define MLX_KEY_PRESS 2

# define KEYPRESS_W 119
# define KEYPRESS_A 97
# define KEYPRESS_S 115
# define KEYPRESS_D 100
# define ESC 65307

#endif