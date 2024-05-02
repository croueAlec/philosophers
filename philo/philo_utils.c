/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:44:06 by acroue            #+#    #+#             */
/*   Updated: 2024/05/02 14:41:50 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_usleep(__useconds_t usec, t_mutex *run, t_philo *philo)
{
	size_t	i;
	size_t	nbr_of_naps;

	i = 0;
	// printf("a\n");
	if (is_philo_dead(philo) == 2)
		return (0);
	if (usec < USLEEP_DELAY)
		return ((void)usleep(usec), 1);
	nbr_of_naps = usec / USLEEP_DELAY;
	while (i < nbr_of_naps && get_mutex_var(run) == RUNNING)
	{
		usleep(USLEEP_DELAY);
		i++;
	}
	printf("salut\n");
	return (i == nbr_of_naps);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;

	if (nmemb * size > 2147483647 || ((nmemb * size < nmemb) \
	&& (nmemb * size < size)))
		return (0);
	buffer = malloc(nmemb * size);
	if (!buffer)
		return (NULL);
	memset(buffer, '\0', nmemb * size);
	return (buffer);
}

time_t	get_curr_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) < 0)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

time_t	time_since_start(t_philo *philo)
{
	return (get_curr_time() - philo->par->time_start);
}

/* 
int	main(int argc, char *argv[])
{
	// ft_usleep(4000000);
	sleep(4);
	return (0);
} */
