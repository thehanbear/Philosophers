/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlee-sun <hlee-sun@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:09:02 by hlee-sun          #+#    #+#             */
/*   Updated: 2024/07/17 14:10:02 by hlee-sun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_philo *philo)
{
	if (philo->moni->num_of_philo % 2 == 0)
		get_forks_together(philo);
	else
		get_forks_one_by_one(philo);
	if (finished(philo->moni) == 1)
		return ;
	pthread_mutex_lock(&philo->eat);
	print_status(philo, "is eating");
	philo->last_eat = curr_time();
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->eat);
	sleep_for(philo->moni->time_to_eat);
	release_forks(philo);
}

static void	*philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 1)
		sleep_for(5);
	while (finished(philo->moni) == 0)
	{
		philo_eat(philo);
		if (finished(philo->moni) == 1)
			break ;
		print_status(philo, "is sleeping");
		sleep_for(philo->moni->time_to_sleep);
		if (finished(philo->moni) == 1)
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
