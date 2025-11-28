SERVER = server.a
CLIENT = client.a

NAME= minitalk
CC = cc
INCLUDE_DIR = include
OBJ_DIR = obj
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = src
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS_CLIENT = $(SRC_DIR)/client.c $(SRC_DIR)/utils.c
SRCS_SERVER = $(SRC_DIR)/server.c $(SRC_DIR)/utils.c

OBJS_CLIENT= $(SRCS_CLIENT:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_SERVER = $(SRCS_SERVER:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

all:  $(OBJ_DIR) $(NAME)

$(OBJ_DIR): 
	mkdir -p obj

$(NAME): $(CLIENT) $(SERVER)

$(SERVER): $(OBJS_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBFT) -o $(SERVER)

$(CLIENT): $(OBJS_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBFT) -o $(CLIENT)	

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	rm -rf obj

fclean: clean
	rm -rf $(CLIENT)
	rm -rf $(SERVER)
	make -C $(LIBFT_DIR) fclean

re: fclean all

PHONY: all clean fclean re 