#include "philo.h"

int	main(int argc, char **argv)
{
	t_moni	moni;

	if (init(&moni, argc, argv) < 0)
		return (1);
	threads(&moni);
	clean_up(&moni);
	return (0);
}
