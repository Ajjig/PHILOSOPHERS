/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majjig <majjig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:15:07 by majjig            #+#    #+#             */
/*   Updated: 2022/02/22 21:04:54 by majjig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_pids	*pid_new(void)
{
	t_pids	*new;

	new = (t_pids *) malloc(sizeof(t_pids));
	new -> next = NULL;
	return (new);
}

t_pids	*pids_handler(int number_of_philosophers)
{
	t_pids	*pids;
	t_pids	*new;

	pids = (t_pids *) malloc(sizeof(t_pids));
	pids -> next = NULL;
	new = pids;
	while (--number_of_philosophers)
	{
		new -> next = pid_new();
		new = new -> next;
		new -> next = NULL;
	}
	return (pids);
}

t_philo	*creat_philos(int ac, char **av)
{
	t_philo	*head;
	int		i;

	i = 2;
	head = (t_philo *) malloc(sizeof(t_philo));
	if (head == NULL)
		return (NULL);
	head -> nth = 0;
	head -> nof = ft_atoi(av[1]);
	head -> time_to_die = ft_atoi(av[2]);
	head -> time_to_eat = ft_atoi(av[3]);
	head -> time_to_sleep = ft_atoi(av[4]);
	head -> number_of_times_each_philosopher_must_eat = -1;
	head -> last_eat = 0;
	if (ac == 6)
		head -> number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	unlink_sems();
	return (head);
}

void	philo_routine(t_philo *philo, t_sems *sems, unsigned long long start)
{
	pthread_t						th;

	pthread_create(&th, NULL, &health_center, philo);
	while (1)
	{
		if (runtime_to_ms(start) == 0 && philo -> nth % 2 == 0)
			usleep(philo -> time_to_eat * 1000);
		sem_wait(sems -> forks);
		put(philo, FORK, sems -> pen);
		philo -> current = EAT;
		sem_wait(sems -> forks);
		put(philo, FORK, sems -> pen);
		philo -> last_eat = runtime_to_ms(start);
		put(philo, EAT, sems -> pen);
		usleep(philo->time_to_eat * 1000);
		if (philo -> number_of_times_each_philosopher_must_eat > 0)
			philo -> number_of_times_each_philosopher_must_eat--;
		put(philo, SLEEP, sems -> pen);
		sem_post(sems -> forks);
		sem_post(sems -> forks);
		usleep(philo -> time_to_sleep * 1000);
		put(philo, THINK, sems -> pen);
		philo -> current = THINK;
	}
}

int	main(int ac, char **av)
{
	t_philo			*head;
	int				pid;
	pthread_t		thread;
	t_pids			*temp;
	t_sems			sems;

	head = args_checker(ac, av, &sems);
	temp = head -> pids;
	pid = getpid();
	while (head -> nof --)
	{
		if (getpid() == pid)
		{
			temp -> pid = fork();
			temp = temp -> next;
			head -> nth ++;
		}
	}
	head -> nof = ft_atoi(av[1]);
	head -> start = runtime_to_ms(0);
	if (pid != getpid())
		philo_routine(head, head -> sems, head -> start);
	pthread_create(&thread, NULL, &wait_for_all, head);
	sem_wait(head -> sems -> one);
	free_clear(head, head -> sems);
}
