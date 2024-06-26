/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:43:04 by acroue            #+#    #+#             */
/*   Updated: 2024/05/06 09:57:19 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_philo_atoi(const char *nptr)
{
	int		i;
	int		sign;
	long	result;

	result = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while ((nptr[i] >= '0' && nptr[i] <= '9') && nptr[i] != '\0')
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	if (result > INT_MAX || result < INT_MIN || ft_strlen((char *)nptr) > 10)
		return (0);
	return (result * sign);
}

/**
 * @brief Check validity of args and set them in the *par Parameter structure.
 * @return int (0) on error, (1) otherwise.
 */
int	arg_check(int argc, char **argv, t_params *par)
{
	size_t	i;
	int		j;

	j = argc;
	if (argc < 5 || argc > 6)
		return (0);
	while (--j > 0)
	{
		i = 0;
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9')
				return (0);
			i++;
		}
	}
	par->min_meal = 0;
	if (argc == 6)
		par->min_meal = ft_philo_atoi(argv[5]);
	par->philo_nbr = ft_philo_atoi(argv[1]);
	par->time_to_die = ft_philo_atoi(argv[2]) * 1000;
	par->time_to_eat = ft_philo_atoi(argv[3]) * 1000;
	par->time_to_sleep = ft_philo_atoi(argv[4]) * 1000;
	return ((argc == 5 || par->min_meal > 0) && par->philo_nbr <= 300 && 0 < (\
	par->philo_nbr * par->time_to_die * par->time_to_eat * par->time_to_sleep));
}

/**
 * @brief They think therefore they are.
 */
static int	define_philosopher(t_philo *p, t_params *par, size_t philo_number)
{
	p->meals_to_eat = par->min_meal;
	p->philo_id = philo_number + 1;
	p->status = THINKING;
	p->par = par;
	p->last_meal = get_curr_time();
	return (init_thread(p, &par->forks[philo_number], AVAILABLE_FORK));
}

t_philo	*free_philos(t_philo *table, size_t index, t_params *par)
{
	size_t	i;

	i = 0;
	while (get_mutex_var(&par->run) == RUNNING)
	{
		usleep(1000);
		if ((size_t)get_mutex_var(&par->full_courses_eaten) == par->philo_nbr)
		{
			set_mutex_var(&par->run, WAITING);
		}
	}
	while (i < index)
	{
		pthread_join(table[i].thread_id, NULL);
		pthread_mutex_destroy(&table[i].own_fork->mutex);
		i++;
	}
	free(table);
	pthread_mutex_destroy(&par->full_courses_eaten.mutex);
	pthread_mutex_destroy(&par->run.mutex);
	pthread_mutex_destroy(&par->write.mutex);
	return (free(par->forks), NULL);
}

/**
 * @brief Creates the philosophers that eat at the **table.
 */
t_philo	*create_philosophers(t_params *par)
{
	t_philo	*table;
	size_t	i;

	i = 0;
	par->time_start = get_curr_time();
	if (par->time_start == -1)
		return ((void)write(2, TIM_ERR, 20), NULL);
	table = ft_calloc(par->philo_nbr, sizeof(t_philo));
	if (!table)
		return ((void)write(2, MAL_ERR, 14), NULL);
	par->forks = ft_calloc(par->philo_nbr, sizeof(t_mutex));
	if (!par->forks)
		return ((void)write(2, MAL_ERR, 14), free(table), NULL);
	while (i < par->philo_nbr)
	{
		define_philosopher(&table[i], par, i);
		if (!table[i].thread_id)
			return (free_philos(table, i, par));
		usleep(300);
		i++;
	}
	while (i--)
		table[i].other_fork = table[(1 + i) % par->philo_nbr].own_fork;
	return (table);
}
