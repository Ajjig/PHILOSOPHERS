NAME = philo

SRCS = philo.c

INC = philo.h

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(OBJS) $(INC)
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	-@rm -rf $(OBJS)

fclean: clean
	-@rm -rf $(NAME)

re: fclean all
