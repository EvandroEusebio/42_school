NAME_EXECUTABLE = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include/so_long.h
MAP_DIR = map
GAME_DIR = game
GRAPHIC_DIR = graphic
LIBFT_DIR = libft
FT_PRINTF_DIR = ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
LIBFT = $(LIBFT_DIR)/libft.a
MLX_PATH = minilibx-linux

MLX = -L$(MLX_PATH) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

SRC = $(SRC_DIR)/utils.c \
      $(SRC_DIR)/$(MAP_DIR)/map_validations.c \
      $(SRC_DIR)/$(MAP_DIR)/map_utils.c \
      $(SRC_DIR)/$(MAP_DIR)/map.c \
      $(SRC_DIR)/$(GAME_DIR)/inicialize.c \
      $(SRC_DIR)/$(GAME_DIR)/events.c \
      $(SRC_DIR)/$(GAME_DIR)/game.c \
      $(SRC_DIR)/$(GRAPHIC_DIR)/render.c \
      $(SRC_DIR)/get_next_line.c \
      $(SRC_DIR)/validate_name_file.c \
      $(SRC_DIR)/exceptions.c \
      $(SRC_DIR)/main.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME_EXECUTABLE)

$(NAME_EXECUTABLE): $(OBJ) $(LIBFT) $(FT_PRINTF)
	make -C $(MLX_PATH)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(FT_PRINTF) $(MLX) -o $(NAME_EXECUTABLE)

$(OBJ): $(INCLUDE_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS)  -I$(MLX_PATH) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make -C $(MLX_PATH) clean
	make -C $(LIBFT_DIR) clean
	make -C $(FT_PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME_EXECUTABLE)
	make -C $(LIBFT_DIR) fclean
	make -C $(FT_PRINTF_DIR) fclean

re: fclean all

