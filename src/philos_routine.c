/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maax <maax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:34:02 by maax              #+#    #+#             */
/*   Updated: 2024/03/14 17:25:53 by maax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		printf("%ld %d has taken a fork(R).\n", get_timestamp(philo), philo->id);
		pthread_mutex_lock(philo->l_fork);
		printf("%ld %d has taken a fork(L).\n", get_timestamp(philo), philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		printf("%ld %d has taken a fork(L).\n", get_timestamp(philo), philo->id);
		pthread_mutex_lock(philo->r_fork);
		printf("%ld %d has taken a fork(R).\n", get_timestamp(philo), philo->id);
	}
	init_time_of_death(philo);
	printf("%ld %d is eating.\n", get_timestamp(philo), philo->id);
	usleep(philo->data->time_to_eat * 1000);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}

void	ft_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping.\n", get_timestamp(philo), philo->id);
	usleep(philo->data->time_to_sleep * 1000);
}

void	ft_think(t_philo *philo)
{
	printf("%ld %d is thinking.\n", get_timestamp(philo), philo->id);
}

void	*philos_routine(void *struct_philo)
{
	t_philo	*philo;

	philo = (t_philo *)struct_philo;
	while (!philo->data->dead_philo)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (0);
}
