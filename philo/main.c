/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:43:07 by acroue            #+#    #+#             */
/*   Updated: 2024/04/30 11:30:31 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i] != '\0')
		i++;
	return (i);
}

static void	print_stats(t_params *par)
{
	printf("%zu Philosophers\nThey take :\n\t\t%zu Useconds to die\n\t\
	%zu Useconds to eat\n\t\t%zu Useconds to sleep\n", par->philo_nbr, \
	par->time_to_die, par->time_to_eat, par->time_to_sleep);
	if (par->min_meal)
		printf("and they all need to eat at least %zu times.\n", par->min_meal);
}

/**
 * @brief Initializes the Run, Write and Full_courses_eaten mutexes.
 * @return 0 on mutex_init error, 1 otherwise.
 */
int	define_params_mutex(t_mutex *courses, t_mutex *run, t_mutex *write)
{
	courses = init_mutex(courses, 0);
	if (!courses)
		return (0);
	run = init_mutex(run, WAITING);
	if (!run)
		return ((void)pthread_mutex_destroy(&courses->mutex), 0);
	write = init_mutex(write, 1);
	if (!write)
	{
		pthread_mutex_destroy(&courses->mutex);
		return ((void)pthread_mutex_destroy(&run->mutex), 0);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_params	par;
	t_philo		*table;

	if (!arg_check(argc, argv, &par))
		return ((void)write(2, EBAD_ARG, ft_strlen(EBAD_ARG)), 1);
	write(1, "Nul n'entre ici s'il n'est philosophe\n", 39);
	print_stats(&par);
	if (!define_params_mutex(&par.full_courses_eaten, &par.run, &par.write))
		return ((void)write(2, "Mutex fail.\n", 13), 3);
	table = create_philosophers(&par);
	if (!table)
		return (2);
	set_mutex_var(&par.run, RUNNING);
	return (free_philos(table, par.philo_nbr, &par), 0);
}
