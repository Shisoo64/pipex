SRCS =	src/main.c \
	src/utils.c

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror

LIBFT = libft/libft.a

NAME = pipex

OBJS = $(SRCS:.c=.o)

all : $(NAME)

.c.o :
	$(CC) $(CFLAGS) -Llibft -lft -c $< -o $(<:.c=.o)

$(LIBFT) :
	make -C libft/

$(NAME) : comp $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(CFLAGS) -Llibft -lft  -o $(NAME)
	@echo "\033[1;32m📦 Program compiled!\033[0m"

commit :
	git add *
	git commit -m "Update"

comp :
	@echo "\e[1;5m🗜️  Program compiling...\033[0m"

clean :
	rm -f $(OBJS)
	make -C libft/ fclean
	@echo "\033[m🧹 Project cleaned!\033[0m"

fclean : clean
	rm -rf $(NAME)
	@echo "\e[1A\e[K\033[m🧹 Project and executable cleaned!\033[0m"

re : fclean all
	@echo "\033[m🗜️ Remaking project!\033[0m"

.PHONY : all re clean fclean
.SILENT :