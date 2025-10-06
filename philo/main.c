/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpmesquita <jpmesquita@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:34:31 by jpmesquita        #+#    #+#             */
/*   Updated: 2025/10/02 14:49:11 by jpmesquita       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//parsing;
//criar structs e inicializar;
//criar thread para cada filósofo;
//criar rotina
	//a) eat
	//b) sleep
	//c) think
int	main(int ac, char **av)
{
	t_data	data;
	t_philo *philo;

	if (!check_args(ac, av))
		exit(1);
	init_data(ac, av, &data);
	init_forks(&data);
	philo = malloc(sizeof(t_philo) * data.number_of_philos);
	if (!philo)
		return (1);
	init_philos(philo, &data);
	thread_init(&data, philo);

	return(0);
}
