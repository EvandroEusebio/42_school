NAME = push_swap.a

CC = cc 
CFLAGS = -Wall -Wextra -Werror

SRCS = push_swap.c \
	   utils.c \
	   operations.c \
	   index.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re