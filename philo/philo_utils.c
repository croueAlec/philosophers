/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:44:06 by acroue            #+#    #+#             */
/*   Updated: 2024/04/23 15:03:16 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_usleep(__useconds_t usec)
{
	size_t	i;
	size_t	nbr_of_naps;

	i = 0;
	if (usec < USLEEP_DELAY)
		return (usleep(usec));
	nbr_of_naps = usec / USLEEP_DELAY;
	while (i < nbr_of_naps)
	{
		usleep(USLEEP_DELAY);
		i++;
	}
	return (i == nbr_of_naps);
}

int	main(int argc, char *argv[])
{
	// ft_usleep(4000000);
	sleep(4);
	return (0);
}
