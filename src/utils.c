#include "philo.h"

int	get_check_nb(char *str)
{
	int		i;
	long	res;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (res > INT_MAX)
			return (print_error("Error: argument range"));
		i++;
	}
	return (res);
}

void	clean_up(t_moni *moni)
{
	int	i;

	i = 0;
	while (i < moni->num_of_philo)
	{
		pthread_mutex_destroy(&moni->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&moni->print_mutex);
	free(moni->philos);
	free(moni->forks);
}

long	curr_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	sleep_for(long time)
{
	long	begin;

	begin = curr_time();
	while (curr_time() < begin + time)
		usleep(500);
}

void	free_forks(t_moni *moni)
{
	int	i;

	i = 0;
	while (i < moni->num_of_philo)
	{
		pthread_mutex_unlock(&moni->forks[i]);
		i++;
	}
}
