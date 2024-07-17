#include "philo.h"

int	print_error(char *message)
{
	printf("%s\n", message);
	return (-1);
}

void	print_status(t_philo *philo, char *status)
{
	long	time;

	pthread_mutex_lock(&philo->moni->print_mutex);
	time = curr_time() - philo->moni->start_time;
	if (!finished(philo->moni))
		printf("%ld %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&philo->moni->print_mutex);
}

void	print_finish(t_moni *moni)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&moni->print_mutex);
	printf("%ld %d died\n", curr_time() - moni->start_time, i + 1);
	pthread_mutex_unlock(&moni->print_mutex);
}
