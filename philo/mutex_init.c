/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:01:06 by acroue            #+#    #+#             */
/*   Updated: 2024/04/30 11:21:28 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*test_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_mutex_var(&philo->par->run) == WAITING)
	{
		usleep(1000);
	}
	printf("J'ai pense, donc je fus %zu\n", philo->philo_id);
	increment_mutex_var(&philo->par->full_courses_eaten);
	return (NULL);
}

t_mutex	*init_mutex(t_mutex *mutex, size_t val)
{
	// printf("\t\t\ti > %zu\n", val);
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
	// printf("\t\t\ti == %zu\n", i);
	return (1);
}
