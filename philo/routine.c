/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:29:45 by acroue            #+#    #+#             */
/*   Updated: 2024/05/03 11:13:58 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eat(t_philo *philo)
{
	if (is_philo_dead(philo))
		return (0);
	if (philo->philo_id % 2)
		if (!pick_up_fork(philo, philo->own_fork))
			return (0);
	if (!pick_up_fork(philo, philo->other_fork))
		return (0);
	if (philo->philo_id % 2 == 0)
		if (!pick_up_fork(philo, philo->own_fork))
			return (0);
	if (print_log(philo, EATING))
		return (0);
	if (!ft_usleep(philo->par->time_to_eat, &philo->par->run, philo))
		return (0);
	put_fork_down(philo);
	philo->last_meal = get_curr_time();
	if (philo->meals_to_eat--)
		if (philo->meals_to_eat == 0)
			increment_mutex_var(&philo->par->full_courses_eaten);
	return (1);
}

int	sleep_routine(t_philo *philo)
{
	if (is_philo_dead(philo))
		return (0);
	if (print_log(philo, SLEEPING))
		return (0);
	return (ft_usleep(philo->par->time_to_sleep, &philo->par->run, philo));
}

int	think(t_philo *philo)
{
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
	return (NULL);
}

//TODO: make cre && valhalla ./philosophers 5 800 200 200 7
// make cre && valhalla ./philosophers 5 800 200 200
