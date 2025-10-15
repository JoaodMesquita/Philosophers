/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals_and_death.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpmesquita <jpmesquita@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:23:49 by jpmesquita        #+#    #+#             */
/*   Updated: 2025/10/15 15:53:04 by jpmesquita       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->data->action);
	dead = philo->data->philo_died;
	pthread_mutex_unlock(&philo->data->action);
	return (dead);
}

int	all_meals(t_philo *philo)
{
	int	meals_done;

	meals_done = 0;
	pthread_mutex_lock(&philo->data->meals_qty);
	meals_done = (philo->meals_eaten == philo->data->num_times_to_eat);
	pthread_mutex_unlock(&philo->data->meals_qty);
	return (meals_done);
}
