/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals_and_death.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpmesquita <jpmesquita@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:23:49 by jpmesquita        #+#    #+#             */
/*   Updated: 2025/10/09 16:34:00 by jpmesquita       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dead(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->data->action);
	dead = philo->data->philo_died;
	pthread_mutex_unlock(&philo->data->action);
}
void	all_meals(t_philo *philo)
{
	int	meals_done;

	pthread_mutex_lock(&philo->data->meals_qty);
	meals_done = (philo->meals_eaten == philo->data->num_times_to_eat);
	pthread_mutex_unlock(&philo->data->meals_qty);
}