/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:10:53 by acroue            #+#    #+#             */
/*   Updated: 2024/04/30 11:21:33 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_mutex_var(t_mutex *mutex)
{
	int	var;

	// printf("%p\n", mutex);
	pthread_mutex_lock(&(mutex->mutex));
	// printf("{%d}\n", mutex->value);
	var = mutex->value;
	pthread_mutex_unlock(&(mutex->mutex));
	return (var);
}

void	set_mutex_var(t_mutex *mutex, int var)
{
	pthread_mutex_lock(&(mutex->mutex));
	mutex->value = var;
	pthread_mutex_unlock(&(mutex->mutex));
}

void	increment_mutex_var(t_mutex *mutex)
{
	pthread_mutex_lock(&(mutex->mutex));
	mutex->value++;
	pthread_mutex_unlock(&(mutex->mutex));
}
