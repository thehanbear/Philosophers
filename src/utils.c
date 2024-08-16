/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlee-sun <hlee-sun@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:09:06 by hlee-sun          #+#    #+#             */
/*   Updated: 2024/07/17 14:10:02 by hlee-sun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_first->mutex);
	pthread_mutex_lock(&philo->fork_second->mutex);
	philo->fork_first->state = 0;
	philo->fork_second->state = 0;
	pthread_mutex_unlock(&philo->fork_second->mutex);
	pthread_mutex_unlock(&philo->fork_first->mutex);
}

void	clean_up(t_moni *moni)
{
	int	i;

	if (moni->forks)
	{
		i = -1;
		while (++i < moni->num_of_philo)
			pthread_mutex_destroy(&moni->forks[i].mutex);
		free(moni->forks);
	}
	if (moni->philos)
	{
		i = -1;
		while (++i < moni->num_of_philo)
			pthread_mutex_destroy(&moni->philos[i].eat);
		free(moni->philos);
	}
	if (moni->mutex_init == 1)
	{
		pthread_mutex_destroy(&moni->print_mutex);
		pthread_mutex_destroy(&moni->finish);
	}
}
