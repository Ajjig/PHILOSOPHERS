/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majjig <majjig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:15:07 by majjig            #+#    #+#             */
/*   Updated: 2022/02/22 00:48:46 by majjig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(char *str)
{
	int	i;
	int	nb;
	int	tmp;

	i = 0;
	nb = 0;
	tmp = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (str[i] - '0') + (nb * 10);
		i++;
		if (nb < tmp)
			return (0);
		tmp = nb;
	}
	if (str[i] != 0)
		return (0);
	return (nb);
}

t_pids	*pid_new(void)
{
	t_pids	*new;

	new = (t_pids *) malloc(sizeof(t_pids));
	new -> next = NULL;
	return (new);
}

t_pids	*pids_handler(number_of_philosophers)
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
void	philo_routine(t_philo *philo, t_sems *sems, unsigned long long int start)
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
	t_sems			sems;
	pthread_t		thread;
	t_pids			*temp;

	if (args_checker(ac, av))
		return (1);
	head = creat_philos(ac, av);
	head -> nof = ft_atoi(av[1]);
	head -> pids = pids_handler(head -> nof);
	temp = head -> pids;
	sems . forks = sem_open("forks", O_CREAT | O_EXCL, 666, head -> nof);
	sems . pen = sem_open("pen", O_CREAT | O_EXCL, 666, 1);
	sems . all = sem_open("all", O_CREAT | O_EXCL, 666, 0);
	sems . one = sem_open("one", O_CREAT | O_EXCL, 666, 0);
	pid = getpid();
	head -> sems = &sems;
	head -> start = runtime_to_ms(0);
	while (head -> nof --)
	{
		if (getpid() == pid)
		{
			temp -> pid = fork();
			temp = temp -> next;
			head -> nth ++;
		}
	}
	if (pid != getpid())
		philo_routine(head, &sems, head -> start);
	head -> nof = ft_atoi(av[1]);
	pthread_create(&thread, NULL, &wait_for_all, head);
	sem_wait(sems . one);
	free_clear(head, &sems);
	return (0);
}
