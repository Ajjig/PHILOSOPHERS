NAME = philo

SRCS =	philo.c \
		philo_utils.c \
		put.c

INC = philo.h

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread

all: $(OBJS) $(INC)
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	-@rm -rf $(OBJS)

fclean: clean
	-@rm -rf $(NAME)

re: fclean all
