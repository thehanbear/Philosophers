/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlee-sun <hlee-sun@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:09:44 by hlee-sun          #+#    #+#             */
/*   Updated: 2024/07/17 14:10:02 by hlee-sun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			pthread_mutex_lock(&moni->print_mutex);
			printf("%ld %d died\n", curr_time() - moni->start_time, i + 1);
			pthread_mutex_unlock(&moni->print_mutex);
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
		if (moni->philos[i].times_eaten >= moni->must_eat)
			ate++;
		pthread_mutex_unlock(&moni->philos[i].eat);
		i++;
	}
	if (ate == moni->num_of_philo)
	{
		pthread_mutex_lock(&moni->finish);
		moni->finish_flag = 1;
		pthread_mutex_unlock(&moni->finish);
		return (1);
	}
	return (0);
}

void	*check_status(void *ptr)
{
	t_moni	*moni;

	moni = (t_moni *)ptr;
	usleep(1000);
	while (1)
	{
		if (find_finish(moni))
			break ;
		if (moni->must_eat > 0 && finish_eating(moni))
			break ;
		usleep(1000);
	}
	return (ptr);
}

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
