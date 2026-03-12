
# Nome do executável final
NAME	= philo

# Compilador e flags obrigatórias da Norma 42
CC		= cc
CFLAGS	= -Wall -Wextra -Werror

# Flag para linkeditar a biblioteca de threads POSIX
LFLAGS	= -lpthread

# Diretório de headers
INC		= -I.

# Lista de todos os arquivos fonte do projeto
SRCS	=	main.c \
			parsing.c \
			utils.c \
			init.c \
			simulation.c \
			routine.c \
			monitor.c \
			free.c

# Transforma os arquivos .c em .o (objetos compilados)
OBJS	= $(SRCS:.c=.o)

# Regra padrão: compila o projeto
all: $(NAME)

# Linka os objetos para gerar o executável final
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)
	@echo "✅  $(NAME) compilado com sucesso!"

# Compila cada arquivo .c em .o, com dependência do header
%.o: %.c philo.h
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Remove os arquivos objetos intermediários
clean:
	rm -f $(OBJS)
	@echo "🧹  Objetos removidos."

# Remove objetos E o executável
fclean: clean
	rm -f $(NAME)
	@echo "🗑️   Executável removido."

# Recompila tudo do zero
re: fclean all

# Declara alvos que não são arquivos reais
.PHONY: all clean fclean re
