/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:41:17 by acroue            #+#    #+#             */
/*   Updated: 2024/04/24 15:36:32 by acroue           ###   ########.fr       */
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

typedef enum e_status
{
	DEAD = 0,
	THINKING = 1,
	EATING = 2,
	SLEEPING = 3
}			t_status;

typedef struct s_arg
{
	int		start;
	size_t	philo_nbr;
	size_t	full_courses_eaten;
}	t_arg;

typedef struct s_parameters
{
	suseconds_t	useconds;
	size_t		philo_nbr;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		min_meal;
}	t_params;

typedef struct s_philosophers
{
	size_t		meals_eaten;
	size_t		meals_to_eat;
	size_t		philo_nbr;
	t_status	status;
	t_params	*par;
}	t_philo;


# define EBAD_ARG "Error, arguments must be positive : \n\
./philosophers number_of_philosopher\
s time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"
# define MAL_ERR "Malloc error\n"
# define TIM_ERR "Failed to get time\n"
# define USLEEP_DELAY 10000

t_philo	**create_philosophers(t_params *par);
int		arg_check(int argc, char **argv, t_params *par);
size_t	ft_strlen(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_free_philo(t_philo **split_array, size_t j);

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
