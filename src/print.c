/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlee-sun <hlee-sun@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:08:56 by hlee-sun          #+#    #+#             */
/*   Updated: 2024/07/17 14:10:02 by hlee-sun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	malloc_error_exit(t_moni *moni)
{
	clean_up(moni);
	print_error("Error: malloc failure");
	exit(1);
}
