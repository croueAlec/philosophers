/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:43:04 by acroue            #+#    #+#             */
/*   Updated: 2024/04/29 16:58:12 by acroue           ###   ########.fr       */
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
	par->time_to_die = ft_philo_atoi(argv[2]);
	par->time_to_eat = ft_philo_atoi(argv[3]);
	par->time_to_sleep = ft_philo_atoi(argv[4]);
	return ((argc == 5 || par->min_meal > 0) && par->philo_nbr <= 300 && 0 < (\
	par->philo_nbr * par->time_to_die * par->time_to_eat * par->time_to_sleep));
}

/**
 * @brief They think therefore they are.
 */
static t_philo	define_philosopher(t_params *par, size_t philo_number)
{
	t_philo	philosopher;

	philosopher.meals_to_eat = par->min_meal;
	philosopher.philo_id = philo_number;
	philosopher.status = THINKING;
	philosopher.par = par;
	init_thread(&philosopher, &par->forks[philo_number], philo_number);
	return (philosopher);
}

t_philo	*free_philos(t_philo *table, size_t index, t_params *par)
{
	size_t	i;

	i = 0;
	while (i < index)
	{
		pthread_join(table[i].thread_id, NULL);
		pthread_mutex_destroy(&table[i].own_fork->mutex);
		i++;
	}
	free(table);
	pthread_mutex_destroy(&par->full_courses_eaten.mutex);
	printf("pasteque %d\n", 15);
	pthread_mutex_destroy(&par->run.mutex);
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
	par->useconds = get_curr_time();
	if (par->useconds == -1)
		return ((void)write(2, TIM_ERR, 20), NULL);
	table = ft_calloc(par->philo_nbr, sizeof(t_philo));
	if (!table)
		return ((void)write(2, MAL_ERR, 14), NULL);
	par->forks = ft_calloc(par->philo_nbr, sizeof(t_mutex));
	if (!par->forks)
		return ((void)write(2, MAL_ERR, 14), free(table), NULL);
	while (i < par->philo_nbr)
	{
		printf("[%zu]\n", i);
		table[i] = define_philosopher(par, i);
		if (!table[i].thread_id)
			return (free_philos(table, i, par));
		usleep(300);
		i++;
	}
	set_mutex_var(&par->run, 1);
	return (table);
}
