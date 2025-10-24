# Executable name
NAME_EXECUTABLE = push_swap

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Paths
SRC_DIR = src
INCLUDE_DIR = include

# Source files (só os nomes)
C_FILES = cust.c operations.c push_swap.c  inicialize.c utils.c position.o moves.c

# Source and object lists
SRC = $(SRC_DIR)/cust.c $(SRC_DIR)/operations.c  $(SRC_DIR)/push_swap.c $(SRC_DIR)/position.c $(SRC_DIR)/stacks.c $(SRC_DIR)/utils.c  $(SRC_DIR)/sort.c $(SRC_DIR)/move_back.c $(SRC_DIR)/moves.c main.c

OBJ = cust.o operations.o push_swap.o inicialize.o utils.o sort.o move_back.o position.o moves.o main.o

# Default target
all: $(NAME_EXECUTABLE)

# Link final executable
$(NAME_EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME_EXECUTABLE) -g

# Compile rule
%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean only object files
clean:
	rm -f $(OBJ)

# Clean all (objects + binary)
fclean: clean
	rm -f $(NAME_EXECUTABLE)

# Rebuild everything
re: fclean all