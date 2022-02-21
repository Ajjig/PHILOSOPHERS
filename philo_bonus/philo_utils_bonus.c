/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajjig <ajjig@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:08:33 by majjig            #+#    #+#             */
/*   Updated: 2022/02/21 18:21:05 by ajjig            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned long long int	runtime_to_ms(unsigned long long int start)
{
	unsigned long long int			ms;
	static struct timeval			time;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000;
	ms += time.tv_usec / 1000;
	return (ms - start);
}

void	free_clear(t_philo *head, t_sems *sems)
{
	t_philo	*next;


	next = head;
	while (next != head && head != NULL)
	{
		head = head -> next;
		kill (head -> pid, SIGTERM);
		free(head);
	}
	sem_close(sems -> pen);
	sem_close(sems -> forks);
	sem_close(sems -> all);
	sem_close(sems -> one);
	sem_unlink("pen");
	sem_unlink("forks");
	sem_unlink("all");
	sem_unlink("one");
}

void	*health_center(void *void_arg)
{
	t_philo					*philo;
	unsigned long long int	start = 0;

	philo = (t_philo *) void_arg;
	if (start == 0)
		start = philo -> start;

	while (1)
	{
		if (philo -> number_of_times_each_philosopher_must_eat == 0)
		{
			sem_post(philo -> sems -> all);
			philo -> number_of_times_each_philosopher_must_eat--;
		}
		if (philo -> last_eat + philo -> time_to_die + 5 < runtime_to_ms(start))
		{
			put(philo, DEAD, philo -> sems -> pen);
			sem_post(philo -> sems -> one);
			exit(0);
		}
	}
	return (NULL);
}

int	args_checker(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac > 6)
		return (write(STDERR_FILENO, "Error:\nToo many args\n", 21));
	if (ac < 5)
		return (write(STDERR_FILENO, "Error:\nArguments needed\n", 24));
	while (i < ac)
		if (ft_atoi(av[i++]) <= 0)
			return (write(STDERR_FILENO, "Error:\nA non-valid argument\n", 28));
	return (0);
}

void	unlink_sems(void)
{
	sem_unlink("forks");
	sem_unlink("pen");
	sem_unlink("one");
	sem_unlink("all");
}