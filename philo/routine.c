/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpmesquita <jpmesquita@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 10:32:15 by jpmesquita        #+#    #+#             */
/*   Updated: 2025/09/28 18:21:52 by jpmesquita       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	//printf timestamp_in_ms "X has taken a fork"
	printf("%ldms philo %d has taken a fork\n", get_current_time() - philo->data->start_time, philo->id);
	pthread_mutex_lock(philo->right_fork);
	printf("%ldms philo %d has taken a fork\n", get_current_time() - philo->data->start_time, philo->id);
	//&philo->data->time_to_eat;

}

void	thinking(t_philo *philo)
 {
	pthread_mutex_lock(&philo->data->action);
	printf("%ldms philo %d is thinking\n", get_current_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->action);
 }

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	eating(philo);
	thinking(philo);
	return (NULL);
}