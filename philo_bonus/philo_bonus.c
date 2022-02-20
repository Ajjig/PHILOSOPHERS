/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajjig <ajjig@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:15:07 by majjig            #+#    #+#             */
/*   Updated: 2022/02/20 23:21:48 by ajjig            ###   ########.fr       */
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

int	new_philo(t_philo *head, int nth, int ac, char **av)
{
	t_philo	*new;

	new = (t_philo *) malloc(sizeof(t_philo));
	if (new == NULL)
	{
		free_clear(head, NULL);
		exit(0);
	}
	while (head->next)
		head = head->next;
	new -> nth = nth;
	new -> time_to_die = ft_atoi(av[2]);
	new -> time_to_eat = ft_atoi(av[3]);
	new -> time_to_sleep = ft_atoi(av[4]);
	new -> number_of_times_each_philosopher_must_eat = -1;
	new -> last_eat = 0;
	if (ac == 6)
		new -> number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	new -> next = NULL;
	head -> next = new;
	return (1);
}

t_philo	*creat_philos(int ac, char **av)
{
	t_philo	*head;
	t_philo	*last;
	int		i;

	i = 2;
	head = (t_philo *) malloc(sizeof(t_philo));
	if (head == NULL)
		return (NULL);
	head -> nth = 1;
	head -> time_to_die = ft_atoi(av[2]);
	head -> time_to_eat = ft_atoi(av[3]);
	head -> time_to_sleep = ft_atoi(av[4]);
	head -> number_of_times_each_philosopher_must_eat = -1;
	head -> last_eat = 0;
	if (ac == 6)
		head -> number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	head->next = NULL;
	while (i <= ft_atoi(av[1]))
		new_philo(head, i++, ac, av);
	last = head;
	while (last->next)
		last = last->next;
	last->next = head;
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
	unsigned int	number_of_philosophers;
	int				pid;
	t_sems			sems;

	if (args_checker(ac, av))
		return (1);
	head = creat_philos(ac, av);
	number_of_philosophers = ft_atoi(av[1]);
	sems . forks = sem_open("forks", O_CREAT | O_EXCL, 666, number_of_philosophers);
	sems . pen = sem_open("pen", O_CREAT | O_EXCL, 666, 1);
	sems . all = sem_open("all", O_CREAT | O_EXCL, 666, 0);
	pid = getpid();
	while (number_of_philosophers--)
	{
		head -> pen = sems . pen;
		head -> start = runtime_to_ms(0);
		if (getpid() == pid)
		{
			head -> pid = fork();
			head = head -> next;
		}
	}
	if (pid != getpid())
		philo_routine(head, &sems, head -> start);
	pthread_create(&sems . thread, NULL, &);
	wait(NULL);
	free_clear(head, &sems);
}
