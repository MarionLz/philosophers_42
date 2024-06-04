/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malauzie <malauzie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:34:02 by maax              #+#    #+#             */
/*   Updated: 2024/06/04 13:37:07 by malauzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_eat(t_philo *philo)
{
	if (!philo->data->stop_simulation)
	{
		take_forks(philo);
		if (philo->data->stop_simulation)
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
			&& !philo->data->stop_simulation)
		{
			pthread_mutex_lock(&philo->meals);
			philo->nb_meals += 1;
			pthread_mutex_unlock(&philo->meals);
		}
	}
}

void	ft_sleep(t_philo *philo)
{
	if (!philo->data->stop_simulation)
	{
		print_message(philo, "is sleeping. 😴\n", 1);
		usleep(philo->data->time_to_sleep * 1000);
	}
}

void	ft_think(t_philo *philo)
{
	if (!philo->data->stop_simulation)
		print_message(philo, "is thinking. 🤔\n", 1);
}

void	*philos_routine(void *struct_philo)
{
	t_philo	*philo;

	philo = (t_philo *)struct_philo;
	while (!philo->data->stop_simulation)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (0);
}
