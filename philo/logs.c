/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:17:53 by acroue            #+#    #+#             */
/*   Updated: 2024/05/03 11:19:34 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char	*find_status(t_status status)
{
	if (status == FORK)
		return ("has taken a fork\n");
	else if (status == EATING)
		return ("is eating\n");
	else if (status == SLEEPING)
		return ("is sleeping\n");
	else if (status == THINKING)
		return ("is thinking\n");
	else if (status == DEAD)
		return ("died\n");
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
