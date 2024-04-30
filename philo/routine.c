/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:29:45 by acroue            #+#    #+#             */
/*   Updated: 2024/04/30 18:46:48 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_log(t_philo *philo, t_status status)
{

	pthread_mutex_lock(&philo->par->write.mutex);
	printf("%ld %zu", time_since_start(philo) / 1000, philo->philo_id);
	if (status == FORK)
		printf(" has taken a fork\n");
	else if (status == EATING)
		printf(" is eating\n");
	else if (status == SLEEPING)
		printf(" is sleeping\n");
	else if (status == THINKING)
		printf(" is thinking\n");
	else if (status == DEAD)
		printf(" died\n");
	pthread_mutex_unlock(&philo->par->write.mutex);
}

void	kill_philo(t_philo *philo)
{
	set_mutex_var(&philo->par->run, WAITING);
	print_log(philo, DEAD);
}

void	eat(t_philo *philo)
{
	printf("%ld et %zu et %zu\n", get_curr_time(), philo->last_meal, (get_curr_time() - philo->last_meal));
	time_t	delay = (get_curr_time() - philo->last_meal) / 1000;
	if (((size_t)delay) > philo->par->time_to_die)
		return ((void)kill_philo(philo));
	pthread_mutex_lock(&philo->own_fork->mutex);
	print_log(philo, FORK);
	pthread_mutex_lock(&philo->own_fork->mutex);
	print_log(philo, FORK);
	print_log(philo, EATING);
	if (!ft_usleep(philo->par->time_to_eat, &philo->par->run))
		return ;
	philo->last_meal = time_since_start(philo);
}
//TODO: finish eat functon

void	*routine(void *varg)
{
	t_philo	*philo;

	philo = (t_philo *)varg;
	while (get_mutex_var(&philo->par->run) == WAITING)
		usleep(500);
	eat(philo);
	if (get_mutex_var(&philo->par->run) == WAITING)
		return (NULL);
	printf("J'ai pense, donc je fus %zu\n", philo->philo_id);
	increment_mutex_var(&philo->par->full_courses_eaten);
	return (NULL);
}
