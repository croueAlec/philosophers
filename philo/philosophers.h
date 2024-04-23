/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:41:17 by acroue            #+#    #+#             */
/*   Updated: 2024/04/23 17:43:58 by acroue           ###   ########.fr       */
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
# include <limits.h>

typedef struct s_arg
{
	int		start;
	size_t	philo_nbr;
	size_t	full_courses_eaten;
}	t_arg;

typedef struct s_parameters
{
	size_t	philo_nbr;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	min_meal;
}	t_params;

# define EBAD_ARG "Error, arguments must be positive : \n\
./philosophers number_of_philosopher\
s time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"

# define USLEEP_DELAY 10000

size_t	ft_strlen(char *str);
int	arg_check(int argc, char **argv, t_params *par);

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
