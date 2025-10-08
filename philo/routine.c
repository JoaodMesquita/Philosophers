/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpmesquita <jpmesquita@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 10:32:15 by jpmesquita        #+#    #+#             */
/*   Updated: 2025/10/08 14:27:30 by jpmesquita       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo)
{
	size_t eat_time;

	eat_time = philo->data->time_to_eat;
	take_forks(philo);
	message("is eating", philo);
	pthread_mutex_lock(&philo->meal);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->meal);
	ft_usleep((eat_time * 1000), philo);
	pthread_mutex_lock(&philo->data->meals_qty);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meals_qty);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		message("has taken a fork", philo);
		pthread_mutex_lock(philo->right_fork);
		message("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		message("has taken a fork", philo);
		pthread_mutex_lock(philo->left_fork);
		message("has taken a fork", philo);
	}
}

static void	sleeping(t_philo *philo)
{
	size_t die_time;
	size_t sleep_time;
	size_t eat_time;

	die_time = philo->data->time_to_die;
	sleep_time = philo->data->time_to_sleep;
	eat_time  = philo->data->time_to_eat;
	message("is sleeping", philo);
	ft_usleep((sleep_time * 1000), philo);
	message("is thinking", philo);
	ft_usleep(((die_time - sleep_time - eat_time) / 4) * 1000, philo);
}

void	*check_if_dead(void *arg)
{
	t_philo	*philo;
	int		i;
	
	philo = (t_philo*)arg;
	while (!philo->data->philo_died)
	{
		i = -1;
		while (++i < philo->data->number_of_philos)
		{
			pthread_mutex_lock(&philo[i].meal);
			if (get_current_time() - philo[i].last_meal >= philo->data->time_to_die)
			{
				message("died", &philo[i]);
				pthread_mutex_lock(&philo->data->action);
				philo->data->philo_died = 1;
				pthread_mutex_unlock(&philo->data->action);
				pthread_mutex_unlock(&philo[i].meal);
				return (NULL);
			}
			pthread_mutex_unlock(&philo[i].meal);
		}
		usleep(500);
	}
	return (NULL);
}


void	*routine(void *arg)
{
	t_philo	*philo;
	philo = (t_philo*)arg;

	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		pthread_mutex_lock(&philo->data->action);
		if (philo->data->philo_died)
		{
			pthread_mutex_unlock(&philo->data->action);
			break ;
		}
		pthread_mutex_unlock(&philo->data->action);
		pthread_mutex_lock(&philo->data->meals_qty);
		if (philo->meals_eaten == philo->data->num_times_to_eat)
		{
			pthread_mutex_unlock(&philo->data->meals_qty);
			break ;
		}
		pthread_mutex_unlock(&philo->data->meals_qty);
		eating(philo);
		sleeping(philo);
	}
	return (NULL);
}
