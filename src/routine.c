#include "philo.h"

int	finished(t_moni *moni)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&moni->finish);
	if (moni->finish_flag)
		ret = 1;
	pthread_mutex_unlock(&moni->finish);
	return (ret);
}

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (finished(philo->moni))
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	if (finished(philo->moni))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->eat);
	print_status(philo, "is eating");
	philo->last_eat = curr_time();
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->eat);
	sleep_for(philo->moni->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	single_philo(t_philo *philo)
{
	sleep_for(philo->moni->time_to_die);
	pthread_mutex_lock(&philo->moni->finish);
	philo->moni->finish_flag = 1;
	pthread_mutex_unlock(&philo->moni->finish);
}

static void	*philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		sleep_for(1);
	while (!finished(philo->moni))
	{
		if (philo->moni->num_of_philo == 1)
		{
			single_philo(philo);
			break ;
		}
		philo_eat(philo);
		if (finished(philo->moni))
			break ;
		print_status(philo, "is sleeping");
		sleep_for(philo->moni->time_to_sleep);
		if (finished(philo->moni))
			break ;
		print_status(philo, "is thinking");
	}
	return (ptr);
}

void	threads(t_moni *moni)
{
	int	i;

	i = 0;
	moni->start_time = curr_time();
	pthread_create(&moni->check_thread, NULL, &check_status, moni);
	while (i < moni->num_of_philo)
	{
		pthread_create(&moni->philos[i].thread, NULL, &philo, &moni->philos[i]);
		i++;
	}
	i = 0;
	pthread_join(moni->check_thread, NULL);
	while (i < moni->num_of_philo)
	{
		pthread_join(moni->philos[i].thread, NULL);
		i++;
	}
}
