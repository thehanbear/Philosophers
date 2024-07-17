#include "philo.h"

static int	init_philo(t_moni *moni)
{
	int	i;

	i = 0;
	moni->philos = malloc(sizeof(t_philo) * moni->num_of_philo);
	if (!moni->philos)
		return (print_error("Error: malloc failure"));
	while (i < moni->num_of_philo)
	{
		moni->philos[i].id = i + 1;
		moni->philos[i].times_eaten = 0;
		moni->philos[i].moni = moni;
		moni->philos[i].left_fork = &moni->forks[i];
		moni->philos[i].right_fork = &moni->forks[(i + 1) % moni->num_of_philo];
		moni->philos[i].last_eat = curr_time();
		if (pthread_mutex_init(&moni->philos[i].eat, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

static int	init_fork(t_moni *moni)
{
	int	i;

	i = 0;
	moni->forks = malloc(sizeof(pthread_mutex_t) * moni->num_of_philo);
	if (!moni->forks)
		return (print_error("Error: malloc failure"));
	while (i < moni->num_of_philo)
	{
		if (pthread_mutex_init(&moni->forks[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

static int	init_mutex(t_moni *moni)
{
	if (pthread_mutex_init(&moni->print_mutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&moni->finish, NULL) != 0)
		return (-1);
	return (0);
}

static int	check_args(t_moni *moni, int argc)
{
	int	ret;

	ret = 0;
	if (moni->num_of_philo < 1 || moni->num_of_philo > 200)
		ret = print_error("Error:  invalid number of philos");
	if (moni->time_to_die < 1)
		ret = print_error("Error:  invalid time to die");
	if (moni->time_to_eat < 1)
		ret = print_error("Error:  invalid time to eat");
	if (moni->time_to_sleep < 1)
		ret = print_error("Error:  invalid time to sleep");
	if (argc == 6)
		if (moni->must_eat < 0)
			ret = print_error("Error:  invalid must eat");
	return (ret);
}

int	init(t_moni *moni, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (print_error("Error: invalid number of arguments"));
	moni->num_of_philo = get_check_nb(argv[1]);
	moni->time_to_die = get_check_nb(argv[2]);
	moni->time_to_eat = get_check_nb(argv[3]);
	moni->time_to_sleep = get_check_nb(argv[4]);
	if (argc == 6)
		moni->must_eat = get_check_nb(argv[5]);
	else
		moni->must_eat = 0;
	moni->finish_flag = 0;
	if (check_args(moni, argc) == -1)
		return (-1);
	if (init_fork(moni) < 0 || init_philo(moni) < 0 || init_mutex(moni) < 0)
		return (print_error("Error: init failure"));
	return (0);
}
