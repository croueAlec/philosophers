/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:03:38 by acroue            #+#    #+#             */
/*   Updated: 2024/05/03 11:05:12 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*find_status(t_status status)
{
	if (status == FORK)
		return("has taken a fork\n");
	else if (status == EATING)
		return("is eating\n");
	else if (status == SLEEPING)
		return("is sleeping\n");
	else if (status == THINKING)
		return("is thinking\n");
	else if (status == DEAD)
		return("died\n");
	else
		return ("won't happen\n");
}

int	print_log(t_philo *philo, t_status status)
{
	pthread_mutex_lock(&philo->par->write.mutex);
	if (get_mutex_var(&philo->par->run) == WAITING && status != DEAD)
		return (pthread_mutex_unlock(&philo->par->write.mutex), 0);
	printf("%ld %zu %s", time_since_start(philo), philo->philo_id, \
	find_status(status));
	pthread_mutex_unlock(&philo->par->write.mutex);
	return (status == DEAD);
}

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
			return ((void)printf("ici\n"), 0);
	}
	set_mutex_var(mutex, philo->philo_id);
	if (is_philo_dead(philo))
		return (kill_philo(philo), 0);
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
	// printf(">%ld %zu", curr, philo->last_meal);
	delay = (curr - philo->last_meal);
	// printf("test %ld %ld\n", delay, (size_t)delay);
	// printf("%zu %zu\n", (size_t)delay, philo->par->time_to_die);
	if (((size_t)delay) > philo->par->time_to_die)
		return ((void)kill_philo(philo), 2);
	if (get_mutex_var(&philo->par->run) == WAITING)
		return (1);
	return (0);
}
