#include "philo.h"

void	put(int nth, int job)
{
	static pthread_mutex_t p;
	static pthread_mutex_t *pen = NULL;

	if (pen == NULL)
	{
		pen = &p;
		pthread_mutex_init(pen, NULL);
	}
	pthread_mutex_lock(pen);
	if (job == FORK)
		printf("%llu %d has taken a fork\n", runtime_to_ms(), nth);
	else if (job == EAT)
		printf("%llu %d is eating\n", runtime_to_ms(), nth);
	else if (job == SLEEP)
		printf("%llu %d is sleeping\n", runtime_to_ms(), nth);
	else if (job == THINK)
		printf("%llu %d is thinking\n", runtime_to_ms(), nth);
	else
	{
		printf("\033[91m%llu %d is dead\n", runtime_to_ms(), nth);
		return;
	}
	pthread_mutex_unlock(pen);
}
