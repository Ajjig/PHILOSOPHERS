/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majjig <majjig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:08:33 by majjig            #+#    #+#             */
/*   Updated: 2022/02/19 23:40:33 by majjig           ###   ########.fr       */
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

void	free_clear(t_philo *head, sem_t *pen, sem_t *forks_available)
{
	t_philo	*next;

	sem_close(pen);
	sem_close(forks_available);
	sem_unlink("pen");
	sem_unlink("forks");
	next = head;
	free(head);
	head = head->next;
	while (next != head && head != NULL)
	{
		free(head);
		head = head->next;
	}
}

void	*health_center(void *void_arg)
{
	t_philo					*philo;
	int						pid;
	unsigned long long int	start = 0;

	philo = (t_philo *) void_arg;
	if (start == 0)
		start = philo -> start;
	pid = getpid();

	while (1)
	{
		if (philo -> last_eat + philo -> time_to_die + 5 < runtime_to_ms(start))
		{
			put(philo, DEAD, philo -> pen);
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
