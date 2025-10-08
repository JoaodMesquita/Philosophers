/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpmesquita <jpmesquita@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:02:50 by jpmesquita        #+#    #+#             */
/*   Updated: 2025/10/08 12:10:15 by jpmesquita       ###   ########.fr       */
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
	else
		data->num_times_to_eat = -1;
	data->start_time = 0;
	pthread_mutex_init(&data->action, NULL);
	pthread_mutex_init(&data->message, NULL);
	pthread_mutex_init(&data->meals_qty, NULL);
}

void	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);
	if (!data->forks)
		return ;
	i = -1;
	while (++i < data->number_of_philos)
		pthread_mutex_init(&data->forks[i], NULL);
}

void	init_philos(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].last_meal = get_current_time();
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->number_of_philos];
		philo[i].data = data;
		pthread_mutex_init(&philo[i].meal, NULL);
	}
}

void	thread_init(t_data *data, t_philo *philo)
{
	int	i;

	data->start_time = get_current_time();
	if (data->number_of_philos == 1)
	{
		one_philo(data, philo);
		return ;
	}
	i = -1;
	while (++i < data->number_of_philos && data->number_of_philos > 1)
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
	pthread_create(&data->monitor, NULL, &check_if_dead, philo);
	i = -1;
	while (++i < data->number_of_philos)
		pthread_join(philo[i].thread, NULL);
	pthread_join(data->monitor, NULL);
}

void	one_philo(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	message("has taken a fork", philo);
	pthread_mutex_unlock(philo->left_fork);
	ft_usleep(philo->data->time_to_die, philo);
	message("died", &philo[0]);
	pthread_mutex_lock(&data->action);
	data->philo_died = 1;
	pthread_mutex_unlock(&data->action);
}