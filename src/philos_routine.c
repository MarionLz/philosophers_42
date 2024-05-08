/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maax <maax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:34:02 by maax              #+#    #+#             */
/*   Updated: 2024/05/08 14:28:26 by maax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		usleep(1000);
		pthread_mutex_lock(philo->r_fork);
		print_message(philo, "has taken a fork(R).\n", 1);
		pthread_mutex_lock(philo->l_fork);
		print_message(philo, "has taken a fork(L).\n", 1);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_message(philo, "has taken a fork(L).\n", 1);
		pthread_mutex_lock(philo->r_fork);
		print_message(philo, "has taken a fork(R).\n", 1);
	}
	init_time_of_death(philo);
	print_message(philo, "is eating.\n", 1);
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
	if (philo->data->nb_each_philo_must_eat != -1 && !philo->data->dead_philo)
	{
		pthread_mutex_lock(&philo->meals);
		philo->nb_meals += 1;
		pthread_mutex_unlock(&philo->meals);
		print_message(philo,"has eaten", 2);
	}
}

void	ft_sleep(t_philo *philo)
{
	print_message(philo, "is sleeping.\n", 1);
	usleep(philo->data->time_to_sleep * 1000);
}

void	ft_think(t_philo *philo)
{
	print_message(philo, "is thinking.\n", 1);
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
