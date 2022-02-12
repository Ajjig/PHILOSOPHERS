#include "philo.h"

void	put(char *str, int nth, int is_dead)
{
	static pthread_mutex_t p;
	static pthread_mutex_t *pen = NULL;

	if (pen == NULL)
	{
		pen = &p;
		pthread_mutex_init(pen, NULL);
	}
	pthread_mutex_lock(pen);
	printf("%llu %d %s", runtime_to_ms(), nth, str);
	if (is_dead == 0)
		pthread_mutex_unlock(pen);
}
