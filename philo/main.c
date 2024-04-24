/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:43:07 by acroue            #+#    #+#             */
/*   Updated: 2024/04/24 15:42:27 by acroue           ###   ########.fr       */
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

static void	print_each_philo(t_philo **table)
{
	size_t	i;
	struct timeval	tv;

	i = 0;
	while (i < table[0]->par->philo_nbr)
	{
		gettimeofday(&tv, NULL);
		printf("je suis le %zu philo\n", table[i]->philo_nbr);
		printf("%zu usec elapsed\n", tv.tv_usec - table[0]->par->useconds);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_params	par;
	t_philo		**table;

	if (!arg_check(argc, argv, &par))
		return ((void)write(2, EBAD_ARG, ft_strlen(EBAD_ARG)), 1);
	write(1, "Nul n'entre ici s'il n'est philosophe\n", 39);
	print_stats(&par);
	table = create_philosophers(&par);
	if (!table)
		return (2);
	print_each_philo(table);
	return (ft_free_philo(table, par.philo_nbr), 0);
}
