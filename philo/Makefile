NAME = philo

SRCS = philo.c

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all:
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	-@rm -rf $(OBJS)

fclean: clean
	-@rm -rf $(NAME)

re: fclean all
