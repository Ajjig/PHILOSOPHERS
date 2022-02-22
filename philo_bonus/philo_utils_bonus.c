/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majjig <majjig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:08:33 by majjig            #+#    #+#             */
/*   Updated: 2022/02/22 21:06:05 by majjig           ###   ########.fr       */
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
	while (head -> pids)
	{
		kill (head -> pids -> pid, SIGQUIT);
		free(head -> pids);
		head -> pids = head -> pids -> next;
	}
	free(head);
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
	unsigned long long int	start;

	philo = (t_philo *) void_arg;
	start = philo -> start;
	while (1)
	{
		if (philo -> number_of_times_each_philosopher_must_eat == 0)
		{
			sem_post(philo -> sems -> all);
			philo -> number_of_times_each_philosopher_must_eat--;
		}
		if (philo -> last_eat + philo -> time_to_die < runtime_to_ms(start))
		{
			put(philo, DEAD, philo -> sems -> pen);
			while (philo -> nof--)
				sem_post(philo -> sems -> all);
			sem_post(philo -> sems -> one);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}

t_philo	*args_checker(int ac, char **av, t_sems *sems)
{
	int		i;
	t_philo	*head;

	i = 1;
	if (ac > 6)
		exit(write(STDERR_FILENO, "Error:\nToo many args\n", 21));
	if (ac < 5)
		exit(write(STDERR_FILENO, "Error:\nArguments needed\n", 24));
	while (i < ac)
		if (ft_atoi(av[i++]) <= 0)
			exit(write(STDERR_FILENO, "Error:\nA non-valid argument\n", 28));
	head = creat_philos(ac, av);
	head -> pids = pids_handler(head -> nof);
	sems -> forks = sem_open("forks", O_CREAT | O_EXCL, 666, head -> nof);
	sems -> pen = sem_open("pen", O_CREAT | O_EXCL, 666, 1);
	sems -> all = sem_open("all", O_CREAT | O_EXCL, 666, 0);
	sems -> one = sem_open("one", O_CREAT | O_EXCL, 666, 0);
	head -> sems = sems;
	return (head);
}

void	unlink_sems(void)
{
	sem_unlink("forks");
	sem_unlink("pen");
	sem_unlink("one");
	sem_unlink("all");
}
