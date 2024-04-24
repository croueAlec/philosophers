/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:43:04 by acroue            #+#    #+#             */
/*   Updated: 2024/04/24 15:42:53 by acroue           ###   ########.fr       */
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
	return ((par->philo_nbr * par->time_to_die * par->time_to_eat * \
	par->time_to_sleep) > 0 && (argc == 5 || par->min_meal > 0));
}

/**
 * @brief They think therefore they are.
 */
static t_philo	*define_philosopher(t_params *par, size_t philo_number)
{
	t_philo	*philosopher;

	philosopher = ft_calloc(1, sizeof(t_philo));
	philosopher->meals_to_eat = par->min_meal;
	philosopher->philo_nbr = philo_number;
	philosopher->status = THINKING;
	philosopher->par = par;
	return (philosopher);
}

/**
 * @brief Creates the philosophers that eat at the **table.
 */
t_philo	**create_philosophers(t_params *par)
{
	t_philo	**table;
	size_t	i;
	struct timeval	tv;

	i = 0;
	if (gettimeofday(&tv, NULL) < 0)
		return ((void)write(2, TIM_ERR, 20), NULL);
	par->useconds = tv.tv_usec;
	table = ft_calloc(par->philo_nbr, sizeof(t_philo *));
	while (i < par->philo_nbr)
	{
		if (!table || (i && !table[i - 1]))
			return ((void)write(2, MAL_ERR, 14), ft_free_philo(table, i), NULL);
		table[i] = define_philosopher(par, i);
		i++;
	}
	return (table);
}
