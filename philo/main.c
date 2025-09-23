/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpmesquita <jpmesquita@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:34:31 by jpmesquita        #+#    #+#             */
/*   Updated: 2025/09/23 22:21:15 by jpmesquita       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_digit(char **av)
{
	int i;
	int j;

	i = 1;
	while(av[i])
	{
		j = 0;
		while(av[i][j])
		{
			if (av[i][j] == '-')
				return(0);
			else if (av[i][j] == '+')
				j++;
			else if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	philos_max_number(char **av)
{
	int	max_number;

	max_number = ft_atoi(av[1]);
	if (max_number > 200 || max_number == 0)
		return (0);
	return (1);
}

int	number_of_meals(int ac, char **av)
{
	int	meals_amount;

	if(ac == 6)
	{
		meals_amount = ft_atoi(av[5]);
		if (meals_amount < 0)
			return (0);
		}
	return (1);
}

void	input_handler(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		write(2, "Wrong number of inputs!\n", 24);
	else if (!is_digit(av))
		write(2, "Only positive numbers!\n", 23);
	else if (!philos_max_number(av))
		write(2, "Philosophers must be 1-200\n", 27);
	else if (!number_of_meals(ac, av)) // provavelmente nao preciso desta funcao.
		write(2, "meals def!\n", 11);
}

int	main(int ac, char **av)
{
	input_handler(ac, av);
	return(0);
}