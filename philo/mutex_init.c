/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:01:06 by acroue            #+#    #+#             */
/*   Updated: 2024/04/29 16:50:59 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*test_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (printf("je suis %zu\n", philo->philo_id) && !get_mutex_var(&philo->par->run))
	{
		usleep(1000);
	}
	return (NULL);
}

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
	if (pthread_create(&philo->thread_id, NULL, &test_routine, philo))
		return (pthread_mutex_destroy(&fork->mutex), 0);
	return (1);
}
