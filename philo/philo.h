/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpmesquita <jpmesquita@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:53:53 by jpmesquita        #+#    #+#             */
/*   Updated: 2025/09/27 20:36:31 by jpmesquita       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data
{
	int		number_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_times_to_eat;
	long	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t action;
	int		philo_died;
}				t_data;

typedef struct s_philo
{
	pthread_t thread;
	int		id;
	int		meals_eaten;
	int		last_meal;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_data *data;
}		t_philo;


int		ft_atoi(const char *nptr);
int		check_args(int ac, char **av);
void	init_data(int ac, char **av, t_data *data);
void	init_forks(t_data *data);
void	init_philos(t_philo *philo, t_data *data);
void	thread_init(t_data *data, t_philo *philo);
void	*routine(void *);
long int		get_current_time(void);

#endif