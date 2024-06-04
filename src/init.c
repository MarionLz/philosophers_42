/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maax <maax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:06:40 by maax              #+#    #+#             */
/*   Updated: 2024/06/04 11:45:30 by maax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_data(int argc, char **argv, t_data *data)
{
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_each_philo_must_eat = ft_atoi(argv[5]);
	else
		data->nb_each_philo_must_eat = -1;
	data->stop_simulation = 0;
	data->all_full = 0;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->full, NULL);
}

int	init_philos(t_data *data)
{
	int i;

	i = 0;
	data->philos = (t_philo *)malloc(data->nb_philos * sizeof(t_philo));
	if (!data->philos)
		return (0);
	while (i < data->nb_philos)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1)% data->nb_philos];
		init_time_of_death(&data->philos[i]);
		data->philos[i].current_time = 0;
		data->philos[i].nb_meals = 0;
		data->philos[i].is_full = false;
		pthread_mutex_init(&data->philos[i].meals, NULL);
		i++;
	}
	return (1);
}

int	init_forks(t_data *data)
{
	int i;

	i = 0;
	data->forks = (pthread_mutex_t *)malloc(data->nb_philos * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (0);
	while (i < data->nb_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (1);
}
