/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majjig <majjig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:12:10 by majjig            #+#    #+#             */
/*   Updated: 2022/02/22 00:46:53 by majjig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* INCLUDES */

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

/* STRUCTS */

typedef struct s_sems
{
	sem_t	*pen;
	sem_t	*forks;
	sem_t	*all;
	sem_t	*one;
}				t_sems;

typedef struct s_pids
{
	int				pid;
	struct s_pids	*next;
}				t_pids;

typedef struct s_philo
{
	int						nth;
	unsigned long long int	current;
	unsigned long long int	time_to_die;
	unsigned long long int	time_to_eat;
	unsigned long long int	time_to_sleep;
	int						nof;
	unsigned long long int	last_eat;
	unsigned long long int	start;
	t_pids					*pids;
	t_sems					*sems;
	unsigned long long int	number_of_times_each_philosopher_must_eat;
}				t_philo;

/* DEFINES */

# define THINK 1
# define EAT 2
# define SLEEP 3
# define FORK 4
# define DEAD 0

/* PROTOTYPES */

unsigned long long int	runtime_to_ms(unsigned long long int start);
void					*health_center(void *void_arg);
int						is_all_eat(t_philo *head);
void					free_clear(t_philo *head, t_sems *sems);
void					philo_routine(t_philo *philo, t_sems *sems, unsigned long long int start);
t_philo					*creat_philos(int ac, char **av);
int						new_philo(t_philo *head, int nth, int ac, char **av);
int						args_checker(int ac, char **av);
int						ft_atoi(char *str);
void					put(t_philo *philo, int job, sem_t *pen);
void					unlink_sems(void);
void					*wait_for_all(void *void_arg);

#endif
