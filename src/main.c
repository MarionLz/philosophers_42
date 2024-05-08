/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maax <maax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:48:25 by maax              #+#    #+#             */
/*   Updated: 2024/05/08 10:27:43 by maax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_check_content_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_args(char **argv)
{
	int i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0 || !ft_check_content_arg(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

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
	
	if (argc < 5 || argc > 6)
		return (printf("Error, the program takes 5 or 6 arguments.\n"), 1);
	if (!ft_check_args(argv))
		return (printf("Error, arguments must be > 0 & can only contain digits.\n"), 1);
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
