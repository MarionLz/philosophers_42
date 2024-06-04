/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malauzie <malauzie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:52:01 by maax              #+#    #+#             */
/*   Updated: 2024/06/04 14:23:28 by malauzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_philo_life(t_philo *philo)
{
	get_current_time(&philo->current_time);
	if (philo->current_time >= philo->time_of_death)
	{
		print_message(philo, "died. 💀\n", 1);
		pthread_mutex_lock(&philo->data->dead);
		philo->data->stop_simulation = 1;
		pthread_mutex_unlock(&philo->data->dead);
	}
}

void	check_nb_meals(t_philo *philo)
{
	if (philo->nb_meals == philo->data->nb_each_philo_must_eat
		&& philo->is_full == false)
	{
		pthread_mutex_lock(&philo->data->full);
		philo->is_full = true;
		philo->data->all_full += 1;
		pthread_mutex_unlock(&philo->data->full);
		print_message(philo, "is full 🫄\n", 1);
	}
	if (philo->data->all_full == philo->data->nb_philos)
	{
		print_message(philo, "🎆🎆 All philos have eaten their meals. 🎆🎆\n", 3);
		pthread_mutex_lock(&philo->data->dead);
		philo->data->stop_simulation = 1;
		pthread_mutex_unlock(&philo->data->dead);
	}
}

void	monitor(t_data *data)
{
	int	i;

	while (data->stop_simulation == 0)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			check_philo_life(&data->philos[i]);
			if (data->nb_each_philo_must_eat != -1)
			{
				check_nb_meals(&data->philos[i]);
			}
			i++;
		}
	}
}
