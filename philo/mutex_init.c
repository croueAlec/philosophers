/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:01:06 by acroue            #+#    #+#             */
/*   Updated: 2024/05/03 11:16:22 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_mutex	*init_mutex(t_mutex *mutex, size_t val)
{
	if (pthread_mutex_init(&mutex->mutex, NULL))
		return (NULL);
	mutex->value = val;
	return (mutex);
}

int	init_thread(t_philo *philo, t_mutex *fork, size_t i)
{
	fork = init_mutex(fork, i);
	if (!fork)
		return (0);
	philo->own_fork = fork;
	if (pthread_create(&philo->thread_id, NULL, &routine, philo))
		return (pthread_mutex_destroy(&fork->mutex), 0);
	return (1);
}
