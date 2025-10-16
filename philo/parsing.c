/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpmesquita <jpmesquita@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 22:48:14 by jpmesquita        #+#    #+#             */
/*   Updated: 2025/10/16 11:48:53 by jpmesquita       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_digit(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == '+' || av[i][j] == '-')
				j++;
			else if (!(av[i][j] >= '0' && av[i][j] <= '9'))
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

int	time_values(char **av)
{
	int	i;

	i = 2;
	while (av[i])
	{
		if ((ft_atoi(av[i]) < 0 && i != 5))
			return (0);
		i++;
	}
	return (1);
}

static int	number_of_meals(int ac, char **av)
{
	int	meals_amount;

	if (ac == 6)
	{
		meals_amount = ft_atoi(av[5]);
		if (meals_amount < 0 || meals_amount > 2147483647)
			return (0);
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (write(2, "Error\nWrong number of inputs!\n", 30), 0);
	else if (!is_digit(av))
		return (write(2, "Error\nOnly digits!\n", 19), 0);
	else if (!philos_max_number(av))
		return (write(2, "Error\nPhilosophers must be 1-200\n", 33), 0);
	else if (!time_values(av))
		return (write(2, "Error\nTime values must be > 0ms\n", 32), 0);
	else if (!number_of_meals(ac, av))
		return (write(2, "Error\nNumber of meals must be >= 0\n", 35), 0);
	return (1);
}
