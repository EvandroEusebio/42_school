NAME_EXECUTABLE = so_long

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include
MAP_DIR = map
GAME_DIR = game
GRAPHIC_DIR = graphic
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_PATH = mlx

MLX = -L$(MLX_PATH) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

SRC = $(SRC_DIR)/utils.c \
      $(SRC_DIR)/$(MAP_DIR)/map_validations.c \
      $(SRC_DIR)/$(MAP_DIR)/map_utils.c \
      $(SRC_DIR)/$(MAP_DIR)/map.c \
      $(SRC_DIR)/$(GAME_DIR)/inicialize.c \
      $(SRC_DIR)/get_next_line.c \
      $(SRC_DIR)/main.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME_EXECUTABLE)

$(NAME_EXECUTABLE): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME_EXECUTABLE)


$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(MLX_PATH) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME_EXECUTABLE)
	make -C $(LIBFT_DIR) fclean

re: fclean all
