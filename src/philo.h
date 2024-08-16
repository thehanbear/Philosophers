/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlee-sun <hlee-sun@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:08:51 by hlee-sun          #+#    #+#             */
/*   Updated: 2024/07/17 14:10:02 by hlee-sun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define INT_MAX 2147483647

typedef struct s_fork
{
	int				state;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int				id;
	long			times_eaten;
	long			last_eat;
	pthread_t		thread;
	t_fork			*fork_first;
	t_fork			*fork_second;
	pthread_mutex_t	eat;
	struct s_moni	*moni;
}	t_philo;

typedef struct s_moni
{
	int				num_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				must_eat;
	int				finish_flag;
	int				mutex_init;
	t_philo			*philos;
	pthread_t		check_thread;
	t_fork			*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	finish;
}	t_moni;

int		init(t_moni *moni, int argc, char **argv);
int		finished(t_moni *moni);
int		get_check_nb(char *str);
int		print_error(char *message);
long	curr_time(void);
void	threads(t_moni *moni);
void	clean_up(t_moni *moni);
void	print_status(t_philo *philo, char *status);
void	sleep_for(long time);
void	*check_status(void *ptr);
void	malloc_error_exit(t_moni *moni);
void	get_philo_forks(t_moni *moni, int i);
void	get_forks_together(t_philo *philo);
void	get_forks_one_by_one(t_philo *philo);
void	release_forks(t_philo *philo);

#endif