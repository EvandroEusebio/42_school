NAME_EXECUTABLE = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = includes/push_swap.h
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = $(SRC_DIR)/cust.c $(SRC_DIR)/operations.c $(SRC_DIR)/stack.c \
      $(SRC_DIR)/push_swap.c $(SRC_DIR)/position.c $(SRC_DIR)/utils.c \
      $(SRC_DIR)/sort.c $(SRC_DIR)/move_back.c $(SRC_DIR)/moves.c \
      $(SRC_DIR)/inicialize.c $(SRC_DIR)/main.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME_EXECUTABLE)



$(NAME_EXECUTABLE): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME_EXECUTABLE)


$(OBJ): $(INCLUDE_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@



clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME_EXECUTABLE)
	make -C $(LIBFT_DIR) fclean

re: fclean all