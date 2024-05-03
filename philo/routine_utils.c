/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:03:38 by acroue            #+#    #+#             */
/*   Updated: 2024/05/03 16:49:02 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	kill_philo(t_philo *philo)
{
	if (get_mutex_var(&philo->par->run) == WAITING)
		return ;
	set_mutex_var(&philo->par->run, WAITING);
	print_log(philo, DEAD);
}

int	pick_up_fork(t_philo *philo, t_mutex *mutex)
{
	while (get_mutex_var(mutex) != AVAILABLE_FORK)
	{
		if (!ft_usleep(100, &philo->par->run, philo))
			return (0);
	}
	set_mutex_var(mutex, philo->philo_id);
	if (is_philo_dead(philo))
		return (0);
	print_log(philo, FORK);
	return (1);
}

void	put_fork_down(t_philo *philo)
{
	set_mutex_var(philo->own_fork, AVAILABLE_FORK);
	set_mutex_var(philo->other_fork, AVAILABLE_FORK);
}

int	is_philo_dead(t_philo *philo)
{
	time_t	curr;
	time_t	delay;

	curr = get_curr_time();
	delay = (curr - philo->last_meal);
	if (((size_t)delay) > philo->par->time_to_die)
		return ((void)kill_philo(philo), 2);
	if (get_mutex_var(&philo->par->run) == WAITING)
		return (1);
	return (0);
}
