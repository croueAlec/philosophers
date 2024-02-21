/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:41:17 by acroue            #+#    #+#             */
/*   Updated: 2024/02/21 19:54:42 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_arg
{
	int		start;
	size_t	philo_nbr;
}	t_arg;

# define EBAD_ARG "Error, wrong arguments : \
./philosophers number_of_philosopher\
s time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"

#endif

/*
pthread_create,
pthread_detach,
pthread_join,
pthread_mutex_init,
pthread_mutex_destroy,
pthread_mutex_lock,
pthread_mutex_unlock
 */
