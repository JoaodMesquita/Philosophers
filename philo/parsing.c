/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpmesquita <jpmesquita@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 22:48:14 by jpmesquita        #+#    #+#             */
/*   Updated: 2025/09/24 00:19:52 by jpmesquita       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int is_digit(char **av)
{
	int i;
	int j;

	i = 1;
	while(av[i])
	{
		j = 0;
		while(av[i][j])
		{
			if (av[i][j] == '+')
				j++;
			else if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return(0);
			if (ft_atoi(av[i]) <= 0 && i != 5)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	philos_max_number(char **av)
{
	int	max_number;
	
	max_number = ft_atoi(av[1]);
	if (max_number > 200 || max_number < 1)
		return (0);
	return (1);
}

void	check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		write(2, "Wrong number of inputs!\n", 24);
		exit(1);
	}
	else if (!is_digit(av))
	{
		write(2, "Only positive numbers!\n", 23);
		exit(1);
	}
	else if (!philos_max_number(av))
	{
		write(2, "Philosophers must be 1-200\n", 27);
		exit(1);
	}
}