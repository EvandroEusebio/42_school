NAME_EXECUTABLE = push_swap

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

SRC = $(SRC_DIR)/cust.c $(SRC_DIR)/operations.c  $(SRC_DIR)/push_swap.c $(SRC_DIR)/position.c $(SRC_DIR)/stacks.c $(SRC_DIR)/utils.c  $(SRC_DIR)/sort.c $(SRC_DIR)/move_back.c $(SRC_DIR)/moves.c $(SRC_DIR)/main.c

OBJ = $(OBJ_DIR)/cust.o $(OBJ_DIR)/operations.o $(OBJ_DIR)/push_swap.o $(OBJ_DIR)/inicialize.o $(OBJ_DIR)/utils.o $(OBJ_DIR)/sort.o $(OBJ_DIR)/move_back.o $(OBJ_DIR)/position.o $(OBJ_DIR)/moves.o $(OBJ_DIR)/main.o

all: $(NAME_EXECUTABLE)

$(NAME_EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME_EXECUTABLE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME_EXECUTABLE)

re: fclean all