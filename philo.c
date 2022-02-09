#include "philo.h"

unsigned long long	runtime_to_ms()
{
	unsigned long long int			ms;
	static unsigned long long int	start = 0;
	static struct timeval			time;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000;
	ms += time.tv_usec / 1000;
	if (!start)
		start = ms;
	return (ms - start);
}

void	free_clear(t_philo *head)
{
	t_philo	*next;

	next = head;
	free(head);
	head = head->next;
	while (next != head)
	{
		free(head);
		head = head->next;
	}
}

void	new_philo(t_philo *head, int nth)
{
	t_philo	*new;

	new = (t_philo *) malloc(sizeof(t_philo));
	while (head->next)
		head = head->next;
	new->nth = nth;
	new->next = NULL;
	head->next = new;
}

t_philo	*creat_philos(int nb)
{
	int		i;
	t_philo	*head;
	t_philo	*last;

	head = (t_philo *) malloc(sizeof(t_philo));
	head->nth = 1;
	head->next = NULL;
	i = 2;
	while (i <= nb)
	{
		new_philo(head, i);
		i++;
	}
	last = head;
	while (last->next)
		last = last->next;
	last->next = head;
	return (head);
}

int	main(int ac,char **av)
{
	int				number_of_philosophers;
	t_philo			*head;
	struct timeval	time;

	number_of_philosophers = atoi(av[1]);
	head = creat_philos(number_of_philosophers);
	head->prev = NULL;
	while (number_of_philosophers--)
	{
		printf(" %d  ", head->nth);
		head = head->next;
	}
	free_clear(head);
}
