/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpmesquita <jpmesquita@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:02:50 by jpmesquita        #+#    #+#             */
/*   Updated: 2025/10/06 11:23:22 by jpmesquita       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(int ac, char **av, t_data *data)
{
	data->number_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->philo_died = 0;
	if (ac == 6)
		data->num_times_to_eat = ft_atoi(av[5]);
	data->start_time = 0;
	pthread_mutex_init(&data->action, NULL);
}

void	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);
	if (!data->forks)
		return ; //dar free com mensagem de Malloc error
	i = -1;
	while (++i < data->number_of_philos)
		pthread_mutex_init(&data->forks[i], NULL);
}

void	init_philos(t_philo *philo, t_data *data)
{
	int i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].last_meal = get_current_time();
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = 0; //valor alterado na criacao da thread
		philo[i].data = data;
		pthread_mutex_init(&philo[i].meal, NULL);
	}
}

void	thread_init(t_data *data, t_philo *philo)
{
	int i;

	data->start_time = get_current_time();
	i = -1;
	while (++i < data->number_of_philos)
	{
		if (data->number_of_philos == 1)
		{
			write(2, "Error\nFailed to create thread\n", 30);
			exit(0);
		}
		philo[i].right_fork = &data->forks[(i + 1) % data->number_of_philos]; //posição atribuida ao r_fork 
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		// criar uma if condition no caso de nao conseguir criar thread e retornar um exit mais free.
	}
	// thread monitor
	pthread_create(&data->monitor, NULL, &check_if_dead, philo);

	i = -1;
	while (++i < data->number_of_philos)
		pthread_join(philo[i].thread, NULL);
	pthread_join(data->monitor, NULL);

}
