/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maax <maax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:52:01 by maax              #+#    #+#             */
/*   Updated: 2024/03/04 09:09:56 by maax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_philo(t_philo *philo)
{
	get_current_time(&philo->current_time);
	if (philo->current_time >= philo->time_of_death)
	{
		printf("%ld %d died.\n", get_timestamp(philo), philo->id);
		philo->status = DEAD;
		philo->data->dead_philo = 1;
	}
}

void	*monitor_routine(void *struct_data)
{
	t_data *data;
	int	i;

	data = (t_data *)struct_data;
	while (data->dead_philo == 0)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			check_philo(&data->philos[i]);
			i++;
		}
	}
	return (0);
}