/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpmesquita <jpmesquita@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:05:23 by jpmesquita        #+#    #+#             */
/*   Updated: 2025/10/05 10:24:05 by jpmesquita       ###   ########.fr       */
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

void	ft_usleep(long miliseconds, t_philo *philo)
{
	long start;

	start = get_current_time();
	while ((get_current_time() - start) < miliseconds)
	{
		pthread_mutex_lock(&philo->data->action);
		if (philo->data->philo_died)
		{
			pthread_mutex_unlock(&philo->data->action);
			return ;
		}
		pthread_mutex_unlock(&philo->data->action);
		usleep(500);
	}
}

long int	get_current_time(void)
{
	struct timeval current_time;

	// obter tempo atual em milissegundos desde 1 de JAN 1970
	gettimeofday(&current_time, NULL);
	//1 seg = 1000ms
	//1ms == 1000 micro segundos
	return((current_time.tv_sec * 1000) + current_time.tv_usec / 1000); 
}

void	message(char *str, t_philo *philo)
{
	size_t timestamp;

	pthread_mutex_lock(&philo->data->action);
	timestamp = get_current_time() - philo->data->start_time;
	printf("%ldms %d %s\n", timestamp, philo->id, str);
	pthread_mutex_unlock(&philo->data->action);
}
