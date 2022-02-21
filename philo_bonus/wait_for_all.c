#include "philo_bonus.h"

void    *wait_for_all(void *void_arg)
{
    t_philo *philo;
    t_philo *next;

    philo = (t_philo *) void_arg;
    next = philo -> next;
    while (next != philo)
    {
        sem_wait(philo -> sems -> all);
        next = next -> next;
    }
    sem_wait(philo -> sems -> all);
    free_clear(philo, philo -> sems);
    exit(0);
    return (NULL);
}