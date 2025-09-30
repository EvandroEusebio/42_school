# Executable name
NAME_EXECUTABLE = push_swap

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Paths
SRC_DIR = src
INCLUDE_DIR = include

# Source files (só os nomes)
C_FILES = cust.c operations.c push_swap.c stacks.c utils.c

# Source and object lists
SRC = $(SRC_DIR)/cust.c $(SRC_DIR)/operations.c $(SRC_DIR)/push_swap.c $(SRC_DIR)/stacks.c $(SRC_DIR)/utils.c  $(SRC_DIR)/sort.c main.c
OBJ = cust.o operations.o push_swap.o stacks.o utils.o sort.o main.o

# Default target
all: $(NAME_EXECUTABLE)

# Link final executable
$(NAME_EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME_EXECUTABLE)

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
