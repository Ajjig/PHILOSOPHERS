/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majjig <majjig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 00:06:42 by majjig            #+#    #+#             */
/*   Updated: 2022/02/22 00:39:03 by majjig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*wait_for_all(void *void_arg)
{
	t_philo	*philo;

	philo = (t_philo *) void_arg;
	while (philo -> pids)
	{
		sem_wait(philo -> sems -> all);
		philo -> pids = philo -> pids -> next;
	}
	sem_post(philo -> sems -> one);
	sem_wait(philo -> sems -> pen);
	return (NULL);
}
