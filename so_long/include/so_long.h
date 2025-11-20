#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stddef.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

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

char **copy_map(char **original_map);
void check_file_name(char *file_name);
void move_player(char type_moviment, t_game *game);
int quit_game(t_game *game);
void game_over(t_game *game);
int key_press(int keycode, t_game *game);
void render_map(t_game *game);
void inicialize_game(t_game *game);
char	*get_next_line(int fd);
void read_store_map(t_game *game, char *source);
char *ft_strcopy(char *dest, const char *src);
char	*ft_strcopy_limit(const char *str, int limit);
int	ft_strlen_without_break(const char *str);
void ft_show_error(char *message);
void ft_show_error_with_free(char *message, char **buffer);
int ft_occur(char *str, char c);
void validation_map(t_game *game);
int ft_open_file(char *source);
int get_quant_rows(char **map);
void ft_show_error_all(char *message, t_game *game);
void	ft_putstr(char *s);


void free_buffer(char **buffer);
int is_retangular(char **map);
int has_allow_char(char **map);
int validade_quant_EPC(char **map);
int check_walls(char **map);
char	*ft_join(char *str1, char *str2);
int is_sorrounded_walls(char **map);
int existType(char **map, char c);
//char **copy_map(char **map, int heigth_map);
void flood_fill(char **map, int x, int y, int width, int height);


#  define BUFFER_SIZE 42
#  define TILE_SIZE 32
#  define LIMIT_WIDTH 1920
#  define LIMIT_HEIGTH 1080

# define MLX_KEY_PRESS 2
# define MLX_CLOSE 17

# define KEYPRESS_W 119
# define KEYPRESS_A 97
# define KEYPRESS_S 115
# define KEYPRESS_D 100
# define ESC 65307

#endif