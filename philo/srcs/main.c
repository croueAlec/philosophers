/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:43:07 by acroue            #+#    #+#             */
/*   Updated: 2024/02/21 19:54:50 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	arg_check(int argc, char **argv)
{
	size_t	i;

	if (argc < 5 || argc > 6)
		return (0);
	while (--argc > 0)
	{
		i = 0;
		while (argv[argc][i])
		{
			if (argv[argc][i] < '0' || argv[argc][i] > '9')
				return (0);
			i++;
		}
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	if (!arg_check(argc, argv))
		return ((void)write(2, EBAD_ARG, ft_strlen(EBAD_ARG)), -1);
	write(1, "Nul n'entre ici s'il n'est philosophe\n", 39);
	return (0);
}
