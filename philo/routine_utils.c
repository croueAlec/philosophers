/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:03:38 by acroue            #+#    #+#             */
/*   Updated: 2024/05/02 16:54:10 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_log(t_philo *philo, t_status status)
{
	pthread_mutex_lock(&philo->par->write.mutex);
	printf("%ld %zu", time_since_start(philo), philo->philo_id);
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
	return (status == DEAD);
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
		return (print_log(philo, DEAD), 0);
	print_log(philo, FORK);
	return (1);
}

void	put_fork_down(t_philo *philo)
{
	set_mutex_var(philo->own_fork, AVAILABLE_FORK);
	set_mutex_var(philo->other_fork, AVAILABLE_FORK);
}

void	kill_philo(t_philo *philo)
{
	set_mutex_var(&philo->par->run, WAITING);
	printf("kill\n");
	print_log(philo, DEAD);
}

int	is_philo_dead(t_philo *philo)
{
	time_t	curr;
	time_t	delay;

	curr = get_curr_time();
	// printf(">%ld %zu", curr, philo->last_meal);
	delay = (curr - philo->last_meal);
	// printf("%zu %zu\n", (size_t)delay, philo->par->time_to_die);
	if (((size_t)delay) > philo->par->time_to_die)
		return ((void)kill_philo(philo), 2);
	if (get_mutex_var(&philo->par->run) == WAITING)
		return (1);
	return (0);
}
