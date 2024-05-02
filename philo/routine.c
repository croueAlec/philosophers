/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:29:45 by acroue            #+#    #+#             */
/*   Updated: 2024/05/02 14:41:11 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eat(t_philo *philo)
{
	if (is_philo_dead(philo))
		return (0);
	if (philo->philo_id % 2)
		if (!pick_up_fork(philo, philo->own_fork) && printf("f1\n"))
			return (0);
	if (!pick_up_fork(philo, philo->other_fork) && printf("f2\n"))
		return (0);
	if (philo->philo_id % 2 == 0 && printf("f3\n"))
		if (!pick_up_fork(philo, philo->own_fork))
			return (0);
	printf("f3\n");
	if (print_log(philo, EATING))
		return (0);
	printf("check %zu\n", philo->philo_id);
	if (!ft_usleep(philo->par->time_to_eat, &philo->par->run, philo))
		return (0);
	philo->last_meal = time_since_start(philo);
	if (philo->meals_to_eat--)
		if (philo->meals_to_eat == 0)
			increment_mutex_var(&philo->par->full_courses_eaten);
	return (1);
}
//TODO: finish eat functon

int	sleep_routine(t_philo *philo)
{
	printf("sleep\n");
	if (is_philo_dead(philo))
		return (0);
	if (print_log(philo, SLEEPING))
		return (0);
	return (ft_usleep(philo->par->time_to_sleep, &philo->par->run, philo));
}

int	think(t_philo *philo)
{
	printf("think\n");
	if (print_log(philo, THINKING))
		return (0);
	return (1);
}

void	*routine(void *varg)
{
	t_philo	*philo;

	philo = (t_philo *)varg;
	while (get_mutex_var(&philo->par->run) == WAITING)
		usleep(500);
	if (philo->philo_id % 2)
		usleep(1000);
	while (eat(philo) && sleep_routine(philo) && think(philo))
		;
	// if (get_mutex_var(&philo->par->run) == WAITING)
	// 	return (NULL);
	printf("J'ai pense, donc je fus %zu\n", philo->philo_id);
	return (NULL);
}
