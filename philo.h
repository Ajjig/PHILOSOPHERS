#ifndef PHILO_H
# define PHILO_H

/* INCLUDES */

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

/* STRUCTS */

typedef struct	s_philo
{
	int		nth;
	struct	s_philo *next;
	struct	s_philo *prev;
}				t_philo;

/* DEFINES */

# define THINK 1
# define EAT 2
# define SLEEP 3

#endif
