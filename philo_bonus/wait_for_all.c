#include "philo_bonus.h"

void    *wait_for_all(void *void_arg)
{
    t_philo *philo;

    philo = (t_philo *) void_arg;
    while (philo -> pids)
    {
        sem_wait(philo -> sems -> all);
        philo -> pids = philo -> pids -> next;
    }
    sem_wait(philo -> sems -> all);
    sem_post(philo -> sems -> one);
    return (NULL);
}
