/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:41:17 by acroue            #+#    #+#             */
/*   Updated: 2024/04/29 15:35:04 by acroue           ###   ########.fr       */
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

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	int				value;
}	t_mutex;

typedef struct s_parameters
{
	suseconds_t	useconds;
	size_t		philo_nbr;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		min_meal;
	t_mutex		*forks;
	t_mutex		run;
	t_mutex		full_courses_eaten;
}	t_params;

typedef struct s_philosophers
{
	size_t		meals_to_eat;
	size_t		philo_id;
	t_status	status;
	t_params	*par;
	t_mutex		*own_fork;
	t_mutex		*other_fork;
	pthread_t	thread_id;
}	t_philo;

# define EBAD_ARG "Error, arguments must be positive, there must be at most \
300 philosophers : \n\
./philosophers number_of_philosopher\
s time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"
# define MAL_ERR "Malloc error\n"
# define TIM_ERR "Failed to get time\n"
# define USLEEP_DELAY 10000

size_t		ft_strlen(char *str);
void		*ft_calloc(size_t nmemb, size_t size);
int			arg_check(int argc, char **argv, t_params *par);
suseconds_t	get_curr_time(void);
int			get_mutex_var(t_mutex *mutex);
void		set_mutex_var(t_mutex *mutex, int var);
t_philo		*create_philosophers(t_params *par);
int			init_thread(t_philo *philo, t_mutex *fork, size_t i);
t_mutex		*init_mutex(t_mutex *mutex, size_t val);
t_philo		*free_philos(t_philo *table, size_t index, t_params *par);

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
