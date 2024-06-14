/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maax <maax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:34:02 by maax              #+#    #+#             */
/*   Updated: 2024/06/14 11:50:17 by maax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_eat(t_philo *philo)
{
	take_forks(philo);
	if (stop_activity(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	init_time_of_death(philo);
	print_message(philo, "is eating. 🍝\n", 1);
	usleep(philo->data->time_to_eat * 1000);
	drop_forks(philo);
	if (philo->data->nb_each_philo_must_eat != -1
		&& !stop_activity(philo))
	{
		pthread_mutex_lock(&philo->meals);
		philo->nb_meals += 1;
		pthread_mutex_unlock(&philo->meals);
	}
}

void	ft_sleep(t_philo *philo)
{
	print_message(philo, "is sleeping. 😴\n", 1);
	usleep(philo->data->time_to_sleep * 1000);
}

void	ft_think(t_philo *philo)
{
	print_message(philo, "is thinking. 🤔\n", 1);
}

void	*philos_routine(void *struct_philo)
{
	t_philo	*philo;

	philo = (t_philo *)struct_philo;
	while (!stop_activity(philo))
	{
		ft_eat(philo);
		if (stop_activity(philo))
			return (NULL);
		ft_sleep(philo);
		if (stop_activity(philo))
			return (NULL);
		ft_think(philo);
	}
	return (NULL);
}
