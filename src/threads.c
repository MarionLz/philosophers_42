/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malauzie <malauzie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:47:13 by maax              #+#    #+#             */
/*   Updated: 2024/06/04 12:04:55 by malauzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	get_current_time(&data->start_time);
	while (i < data->nb_philos)
	{
		pthread_create(&data->philos[i].thread_philo, NULL,
			philos_routine, &data->philos[i]);
		i++;
	}
}

void	wait_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philos[i].thread_philo, NULL);
		i++;
	}
}
