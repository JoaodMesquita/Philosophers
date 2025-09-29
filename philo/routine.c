/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpmesquita <jpmesquita@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 10:32:15 by jpmesquita        #+#    #+#             */
/*   Updated: 2025/09/29 14:14:06 by jpmesquita       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	message("has taken a fork", philo);
	pthread_mutex_lock(philo->right_fork);
	message("has taken a fork", philo);
	ft_usleep(philo->data->time_to_eat);
	message("is eating", philo);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	sleeping(t_philo *philo)
{
	message("is sleeping", philo);
	ft_usleep(philo->data->time_to_sleep);
	message("is thinking", philo);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;

	int i = -1;
	while (++i < philo->data->num_times_to_eat)
	{
		eating(philo);
		sleeping(philo);
	}
	return (NULL);
}