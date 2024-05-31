/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maax <maax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:48:25 by maax              #+#    #+#             */
/*   Updated: 2024/05/31 10:03:31 by maax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	create_threads(t_data *data)
{
	int	i;
	
	i = 0;
	get_current_time(&data->start_time);
	pthread_create(&data->thread_monitor, NULL, monitor_routine, data);
	while (i < data->nb_philos)
	{
		pthread_create(&data->philos[i].thread_philo, NULL, philos_routine, &data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philos[i].thread_philo, NULL);
		i++;
	}
	pthread_join(data->thread_monitor, NULL);
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;

	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(data->philos[i].l_fork);
		pthread_mutex_destroy(data->philos[i].r_fork);
		pthread_mutex_destroy(&data->philos[i].meals);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->full);	
	free(data->forks);
	free(data->philos);
}

void	lonesome_cowboy(t_data *data)
{
	printf("0 1 has taken a fork.\n");
	printf("%d 1 died.\n", data->time_to_die);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_input(argc, argv) == 1)
		return (1);
	init_data(argc, argv, &data);
	if (data.nb_philos == 1)
	{
		lonesome_cowboy(&data);
		return (0);
	}
	if (!init_forks(&data) || !init_philos(&data))
		return (EXIT_FAILURE);
	create_threads(&data);
	free_all(&data);
	return (0);
}
