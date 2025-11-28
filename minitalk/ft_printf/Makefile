CCFLAGS = -Wall -Wextra -Werror
CC = cc
NAME = libftprintf.a
HEADER = ft_printf.h
LIBFT_DIR = ../libft

SRCS = ft_untoa.c ft_verify_c.c ft_printf.c ft_putnbrx_fd.c ft_verify_char.c ft_verify_number.c ft_verify_pointer_p.c ft_verify_string.c ft_verify_unsigned_number.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/libft.a ./libftprintf.a
	ar rcs $(NAME) $(OBJS)

$(OBJS): $(HEADER)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	
re: fclean all

.PHONY: all fclean re clean
