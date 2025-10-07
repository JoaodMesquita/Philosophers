/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpmesquita <jpmesquita@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:53:53 by jpmesquita        #+#    #+#             */
/*   Updated: 2025/10/07 21:26:50 by jpmesquita       ###   ########.fr       */
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
	pthread_t		monitor;
	int				number_of_philos;
	size_t			start_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_times_to_eat;
	int				philo_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	action;
	pthread_mutex_t message;
	pthread_mutex_t meals_qty;
}				t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	size_t			last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal;
	t_data			*data;
}		t_philo;


int				ft_atoi(const char *nptr);
int				check_args(int ac, char **av);
void			init_data(int ac, char **av, t_data *data);
void			init_forks(t_data *data);
void			init_philos(t_philo *philo, t_data *data);
void			thread_init(t_data *data, t_philo *philo);
void			*routine(void *);
long int		get_current_time(void);
void			ft_usleep(long miliseconds, t_philo *philo);
void			message(char *str, t_philo *philo);
void			take_forks(t_philo *philo);
void			*check_if_dead(void *arg);
void			destroy_all_mutexes(t_data *data, t_philo *philo);
void			one_philo(t_data *data, t_philo *philo);

#endif