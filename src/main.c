/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlee-sun <hlee-sun@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:08:46 by hlee-sun          #+#    #+#             */
/*   Updated: 2024/07/17 14:10:02 by hlee-sun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_moni	moni;

	if (init(&moni, argc, argv) != 0)
	{
		clean_up(&moni);
		return (EXIT_FAILURE);
	}
	threads(&moni);
	clean_up(&moni);
	return (EXIT_SUCCESS);
}
