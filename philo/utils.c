/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpmesquita <jpmesquita@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:05:23 by jpmesquita        #+#    #+#             */
/*   Updated: 2025/10/15 16:08:04 by jpmesquita       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * sign);
}

long int	current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + current_time.tv_usec / 1000);
}

void	message(char *str, t_philo *philo)
{
	size_t	timestamp;

	pthread_mutex_lock(&philo->data->action);
	timestamp = current_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->message);
	if (!philo->data->philo_died)
		printf("%ld %d %s\n", timestamp, philo->id, str);
	pthread_mutex_unlock(&philo->data->message);
	pthread_mutex_unlock(&philo->data->action);
}

void	destroy_all_mutexes(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
		pthread_mutex_destroy(&data->forks[i]);
	i = -1;
	while (++i < data->number_of_philos)
		pthread_mutex_destroy(&philo[i].meal);
	free(data->forks);
	pthread_mutex_destroy(&data->action);
	pthread_mutex_destroy(&data->meals_qty);
	pthread_mutex_destroy(&data->message);
	free(philo);
}
