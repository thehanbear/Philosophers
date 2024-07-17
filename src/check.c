#include "philo.h"

static int	find_finish(t_moni *moni)
{
	int	i;

	i = 0;
	while (i < moni->num_of_philo)
	{
		pthread_mutex_lock(&moni->philos[i].eat);
		if (curr_time() - moni->philos[i].last_eat > moni->time_to_die)
		{
			pthread_mutex_lock(&moni->finish);
			moni->finish_flag = 1;
			pthread_mutex_unlock(&moni->finish);
			print_finish(moni);
			free_forks(moni);
			pthread_mutex_unlock(&moni->philos[i].eat);
			return (1);
		}
		pthread_mutex_unlock(&moni->philos[i].eat);
		i++;
	}
	return (0);
}

static int	finish_eating(t_moni *moni)
{
	int	i;
	int	ate;

	i = 0;
	ate = 0;
	while (i < moni->num_of_philo)
	{
		pthread_mutex_lock(&moni->philos[i].eat);
		if (moni->must_eat > 0 && moni->philos[i].times_eaten >= moni->must_eat)
			ate++;
		pthread_mutex_unlock(&moni->philos[i].eat);
		i++;
	}
	if (ate == moni->num_of_philo)
	{
		pthread_mutex_lock(&moni->finish);
		moni->finish_flag = 1;
		free_forks(moni);
		pthread_mutex_unlock(&moni->finish);
		return (1);
	}
	return (0);
}

void	*check_status(void *ptr)
{
	t_moni	*moni;

	moni = (t_moni *)ptr;
	sleep_for(1);
	while (1)
	{
		if (find_finish(moni) || finish_eating(moni))
			break ;
		sleep_for(1);
	}
	return (ptr);
}
