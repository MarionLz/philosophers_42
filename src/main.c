/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maax <maax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:48:25 by maax              #+#    #+#             */
/*   Updated: 2024/06/14 11:55:22 by maax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	lonesome_cowboy(t_data *data)
{
	long int	timestamp;
	long int	current_time;

	current_time = 0;
	get_current_time(&data->start_time);
	get_current_time(&current_time);
	timestamp = current_time - data->start_time;
	printf("%ld 1 has taken a fork. 🍴\n", timestamp);
	usleep(data->time_to_die * 1000);
	get_current_time(&current_time);
	timestamp = current_time - data->start_time;
	printf("%ld 1 died. 💀\n", timestamp);
	free_data(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (!is_input_valid(argc, argv))
		return (1);
	data = malloc(sizeof(*data));
	init_data(argc, argv, data);
	if (data->nb_philos == 1)
	{
		lonesome_cowboy(data);
		return (0);
	}
	if (!init_forks(data) || !init_philos(data))
		return (1);
	create_threads(data);
	monitor(data);
	wait_threads(data);
	free_all(data);
	return (0);
}
