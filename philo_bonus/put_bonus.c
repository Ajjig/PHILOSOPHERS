/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majjig <majjig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 23:17:02 by majjig            #+#    #+#             */
/*   Updated: 2022/02/19 23:34:54 by majjig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	put(t_philo *philo, int job, sem_t *pen)
{
	static unsigned long long int start = 0;

	if (start == 0)
		start = philo -> start;
	sem_wait(pen);
	if (job == FORK)
		printf("%llu %d has taken a fork\n", runtime_to_ms(start), philo -> nth);
	else if (job == EAT)
		printf("%llu %d is eating\n", runtime_to_ms(start), philo -> nth);
	else if (job == SLEEP)
		printf("%llu %d is sleeping\n", runtime_to_ms(start), philo -> nth);
	else if (job == THINK)
		printf("%llu %d is thinking\n", runtime_to_ms(start), philo -> nth);
	else
	{
		printf("%llu %d died\n", runtime_to_ms(start), philo -> nth);
		return ;
	}
	sem_post(pen);
}
