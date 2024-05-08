/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maax <maax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:49:26 by maax              #+#    #+#             */
/*   Updated: 2024/05/08 14:07:25 by maax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
#define	PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>

struct s_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		thread_philo;
	int				id;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	long int		time_of_death;
	long int		current_time;
	int				nb_meals;
	pthread_mutex_t meals;
}	t_philo;

typedef struct s_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_each_philo_must_eat;
	bool			dead_philo;
	pthread_mutex_t dead;
	pthread_t		thread_monitor;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	long int		start_time;
	pthread_mutex_t	print;
	int				all_full;
	pthread_mutex_t full;
}	t_data;

int			ft_atoi(const char *nptr);
void		init_data(int argc, char **argv, t_data *data);
int			init_philos(t_data *data);
int			init_forks(t_data *data);
void		init_time_of_death(t_philo *philo);
void		get_current_time(long int *current_time);
long int	get_timestamp(t_philo *philo);
void		*philos_routine(void *struct_philo);
void		*monitor_routine(void *struct_data);
long int	get_timestamp(t_philo *philo);
void		get_current_time(long int *current_time);
void		print_message(t_philo *philo, char *message, int flag);

# endif