#ifndef PHILO_H
# define PHILO_H

/* INCLUDES */

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

/* STRUCTS */

typedef struct	s_philo
{
	int						nth;
	struct	s_philo			*next;
	pthread_mutex_t			fork;
	pthread_t				thread_data;
	unsigned long long int	current;
	unsigned long long int	time_to_die;
	unsigned long long int	time_to_eat;
	unsigned long long int	time_to_sleep;
	unsigned long long int	last_eat;
	unsigned long long int	n_meals;
	unsigned long long int	number_of_times_each_philosopher_must_eat;
}				t_philo;

/* DEFINES */

# define THINK 1
# define EAT 2
# define SLEEP 3
# define FORK 4
# define DEAD 0

/* PROTOTYPES */

unsigned long long int	runtime_to_ms(void);
void					*health_center(void *void_arg);
int						is_all_eat(t_philo *head);
void					free_clear(t_philo *head);
void					*philo_routine(void *void_arg);
t_philo					*creat_philos(int ac, char **av);
void					new_philo(t_philo *head, int nth, int ac, char **av);
int						args_checker(int ac, char **av);
int						ft_atoi(char *str);
void					put(int nth, int job);

#endif
