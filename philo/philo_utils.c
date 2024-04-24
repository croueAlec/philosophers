/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:44:06 by acroue            #+#    #+#             */
/*   Updated: 2024/04/24 14:55:14 by acroue           ###   ########.fr       */
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

static void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
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
	ft_bzero(buffer, nmemb * size);
	return (buffer);
}

void	ft_free_philo(t_philo **split_array, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		free(split_array[i]);
		i++;
	}
	free(split_array);
	return ;
}

/* 
int	main(int argc, char *argv[])
{
	// ft_usleep(4000000);
	sleep(4);
	return (0);
} */
