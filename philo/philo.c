/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majjig <majjig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:15:07 by majjig            #+#    #+#             */
/*   Updated: 2022/02/16 21:02:19 by majjig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		free_clear(head);
		return (0);
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
		if (new_philo(head, i++, ac, av) == 0)
			return (NULL);
	last = head;
	while (last->next)
		last = last->next;
	last->next = head;
	return (head);
}

void	*philo_routine(void *void_arg)
{
	t_philo	*philo;

	philo = (t_philo *) void_arg;
	while (1)
	{
		if (runtime_to_ms() == 0 && philo -> nth % 2 == 0)
			usleep(philo -> time_to_eat * 1000);
		pthread_mutex_lock(&philo -> fork);
		put(philo -> nth, FORK);
		pthread_mutex_lock(&philo -> next -> fork);
		philo -> current = EAT;
		put(philo -> nth, FORK);
		philo -> last_eat = runtime_to_ms();
		put(philo -> nth, EAT);
		usleep(philo->time_to_eat * 1000);
		if (philo -> number_of_times_each_philosopher_must_eat > 0)
			philo -> number_of_times_each_philosopher_must_eat--;
		put(philo -> nth, SLEEP);
		pthread_mutex_unlock(&philo -> fork);
		pthread_mutex_unlock(&philo -> next -> fork);
		usleep(philo -> time_to_sleep * 1000);
		put(philo -> nth, THINK);
		philo -> current = THINK;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_philo		*head;
	int			number_of_philosophers;
	pthread_t	health;

	if (args_checker(ac, av))
		return (1);
	head = creat_philos(ac, av);
	if (head == NULL)
		return (1);
	number_of_philosophers = ft_atoi(av[1]);
	while (number_of_philosophers--)
	{
		pthread_mutex_init(&head -> fork, NULL);
		pthread_create(&head -> thread_data, NULL, &philo_routine, head);
		head = head->next;
	}
	pthread_create(&health, NULL, &health_center, head);
	pthread_join(health, NULL);
	number_of_philosophers = ft_atoi(av[1]);
	while (number_of_philosophers--)
	{
		pthread_detach(head -> thread_data);
		head = head -> next;
	}
	free_clear(head);
}
