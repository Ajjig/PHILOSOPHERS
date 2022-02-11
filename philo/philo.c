#include "philo.h"

void	new_philo(t_philo *head, int nth, int ac, char **av)
{
	t_philo	*new;

	new = (t_philo *) malloc(sizeof(t_philo));
	while (head->next)
		head = head->next;
	new -> nth = nth;
	new -> time_to_die = atoi(av[2]);
	new -> time_to_eat = atoi(av[3]);
	new -> time_to_sleep = atoi(av[4]);
	new -> number_of_times_each_philosopher_must_eat = -1;
	if (ac == 6)
		new -> number_of_times_each_philosopher_must_eat = atoi(av[5]);
	new -> next = NULL;
	head -> next = new;
}

t_philo	*creat_philos(int ac, char **av)
{
	int		i;
	t_philo	*head;
	t_philo	*last;
	int		number_of_philos;

	number_of_philos = atoi(av[1]);
	head = (t_philo *) malloc(sizeof(t_philo));
	head->nth = 1;
	head -> time_to_die = atoi(av[2]);
	head -> time_to_eat = atoi(av[3]);
	head -> time_to_sleep = atoi(av[4]);
	head -> number_of_times_each_philosopher_must_eat = -1;
	if (ac == 6)
		head -> number_of_times_each_philosopher_must_eat = atoi(av[5]);
	head->next = NULL;
	i = 2;
	while (i <= number_of_philos)
	{
		new_philo(head, i, ac, av);
		i++;
	}
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
		if (philo -> current == THINK || (runtime_to_ms() == 0 && philo -> nth % 2 != 0))
		{
			pthread_mutex_lock(&philo -> fork);
			pthread_mutex_lock(&philo -> next -> fork);
			philo -> current = EAT;
			printf("%llu %d has taken a fork\n", runtime_to_ms(), philo -> nth);
			printf("%llu %d is eating\n", runtime_to_ms(), philo -> nth);
			usleep(philo->time_to_eat * 1000);
			philo -> last_eat = runtime_to_ms();
			if (philo -> number_of_times_each_philosopher_must_eat > 0)
				philo -> number_of_times_each_philosopher_must_eat--;
			pthread_mutex_unlock(&philo -> fork);
			pthread_mutex_unlock(&philo -> next -> fork);
		}
		else if(philo -> current != SLEEP)
		{
			printf("%llu %d is sleeping\n", runtime_to_ms(), philo -> nth);
			philo -> current = SLEEP;
			usleep(philo -> time_to_sleep * 1000);
			printf("%llu %d is thinking\n", runtime_to_ms(), philo -> nth);
			philo -> current = THINK;
		}
	}
	return (NULL);
}

int	main(int ac,char **av)
{
	t_philo		*head;
	int			number_of_philosophers;
	int			i;
	pthread_t	health;

	i = 0;
	if (args_checker(ac, av))
		return (1);
	head = creat_philos(ac, av);
	number_of_philosophers = atoi(av[1]);
	while (i++ < number_of_philosophers)
	{
		pthread_mutex_init(&head -> fork, NULL);
		pthread_create(&head -> thread_data, NULL, &philo_routine, head);
		head = head->next;
	}
	pthread_create(&health, NULL, &health_center, head);
	pthread_join(health, NULL);
	while (i--)
	{
		pthread_detach(head -> thread_data);
		head = head -> next;
	}
	free_clear(head);
}
