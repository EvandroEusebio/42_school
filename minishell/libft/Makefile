# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akudiezo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/26 15:20:39 by akudiezo          #+#    #+#              #
#    Updated: 2025/06/26 15:20:41 by akudiezo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c\
      ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_tolower.c ft_toupper.c\
      ft_strchr.c ft_split.c ft_strncmp.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putendl_fd.c\
      ft_memchr.c ft_memcmp.c ft_strnstr.c ft_strrchr.c ft_strjoin.c ft_substr.c ft_strtrim.c\
      ft_striteri.c ft_putnbr_fd.c ft_atoi.c ft_strdup.c ft_calloc.c ft_putstr_fd.c ft_strjoin3.c\
      ft_isspace.c

OBJ = $(SRC:.c=.o)
DEPS = $(OBJ:.o=.d)

HEADER = libft.h

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Incluir dependências geradas automaticamente
-include $(DEPS)

.PHONY: all clean fclean re
