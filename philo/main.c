/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpmesquita <jpmesquita@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:34:31 by jpmesquita        #+#    #+#             */
/*   Updated: 2025/10/06 15:06:39 by jpmesquita       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	if (!check_args(ac, av))
		exit(1);
	init_data(ac, av, &data);
	init_forks(&data);
	philo = malloc(sizeof(t_philo) * data.number_of_philos);
	if (!philo)
	{
		free(philo);
		return (1);
	}
	init_philos(philo, &data);
	thread_init(&data, philo);
	destroy_all_mutexes(&data, philo);
	return (0);
}
