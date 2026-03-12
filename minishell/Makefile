# Program name
NAME = minishell

# Compilation flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP

# Project files
SRCS = main.c \
	srcs/parsing/tokenizer.c \
	srcs/parsing/parser.c \
	srcs/parsing/syntax_check.c \
	srcs/parsing/quote_expander.c \
	srcs/parsing/quote_validator.c \
	srcs/parsing/var_expander.c \
	srcs/environment/env_manager.c \
	srcs/execution/executor.c \
	srcs/execution/pipe_executor.c \
	srcs/execution/path_finder.c \
	srcs/execution/redirections.c \
	srcs/execution/heredoc.c \
	srcs/builtins/echo.c \
	srcs/builtins/cd.c \
	srcs/builtins/pwd.c \
	srcs/builtins/export.c \
	srcs/builtins/unset.c \
	srcs/builtins/env.c \
	srcs/builtins/exit.c \
	srcs/signals/signals.c \
	srcs/utils/memory_utils.c \
	srcs/utils/error_utils.c \
	srcs/utils/helpers.c \
	srcs/structures/init.c \
	srcs/structures/cleanup.c
	
	
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

# Path to libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Main rule
all: $(NAME)

# Compiling minishell
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -lhistory -o $(NAME)

# Compiling libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Objects clean
clean:
	rm -f $(OBJS) $(DEPS)
	$(MAKE) clean -C $(LIBFT_DIR)

# Clean everything (objects + program + libft)
fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

# Recompiling
re: fclean all

# Include deps
-include $(DEPS)

.PHONY: all clean fclean re
