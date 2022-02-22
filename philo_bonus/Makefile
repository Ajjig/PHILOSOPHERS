NAME = philo_bonus

SRCS =	philo_bonus.c \
		philo_utils_bonus.c \
		put_bonus.c \
		wait_for_all.c \
		atoi.c

INC = philo_bonus.h

OBJS = ${SRCS:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(OBJS) $(INC)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	-@rm -rf $(OBJS)

fclean: clean
	-@rm -rf $(NAME)

re: fclean all

bonus: all
