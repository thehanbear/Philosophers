/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlee-sun <hlee-sun@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:10:24 by hlee-sun          #+#    #+#             */
/*   Updated: 2024/07/17 15:10:02 by hlee-sun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_philo_forks(t_moni *moni, int i)
{
	if (i == moni->num_of_philo - 1)
	{
		moni->philos[i].fork_first = &moni->forks[0];
		moni->philos[i].fork_second = &moni->forks[i];
	}
	else
	{
		moni->philos[i].fork_first = &moni->forks[i];
		moni->philos[i].fork_second = &moni->forks[i + 1];
	}
}

void	get_forks_together(t_philo *philo)
{
	int	got_forks;

	got_forks = 0;
	while (finished(philo->moni) == 0)
	{
		pthread_mutex_lock(&philo->fork_first->mutex);
		pthread_mutex_lock(&philo->fork_second->mutex);
		if (philo->fork_first->state == 0 && philo->fork_second->state == 0)
		{
			philo->fork_first->state = 1;
			philo->fork_second->state = 1;
			got_forks = 1;
		}
		pthread_mutex_unlock(&philo->fork_second->mutex);
		pthread_mutex_unlock(&philo->fork_first->mutex);
		if (got_forks == 1)
		{
			print_status(philo, "has taken a fork");
			print_status(philo, "has taken a fork");
			break ;
		}
		usleep(100);
	}
}

static int	try_get_first(t_philo *philo)
{
	int	got_fork;

	got_fork = 0;
	pthread_mutex_lock(&philo->fork_first->mutex);
	if (philo->fork_first->state == 0)
	{
		philo->fork_first->state = 1;
		got_fork = 1;
		print_status(philo, "has taken a fork");
	}
	pthread_mutex_unlock(&philo->fork_first->mutex);
	return (got_fork);
}

static int	try_get_second(t_philo *philo)
{
	int	got_fork;

	got_fork = 0;
	pthread_mutex_lock(&philo->fork_second->mutex);
	if (philo->fork_second->state == 0)
	{
		philo->fork_second->state = 1;
		got_fork = 1;
		print_status(philo, "has taken a fork");
	}
	pthread_mutex_unlock(&philo->fork_second->mutex);
	return (got_fork);
}

void	get_forks_one_by_one(t_philo *philo)
{
	int	got_first;
	int	got_second;

	got_first = 0;
	got_second = 0;
	while (finished(philo->moni) == 0)
	{
		if (got_first == 0)
			got_first = try_get_first(philo);
		if (got_first == 1 && got_second == 1)
			break ;
		if (got_second == 0)
			got_second = try_get_second(philo);
		if (got_first == 1 && got_second == 1)
			break ;
		usleep(100);
	}
}
