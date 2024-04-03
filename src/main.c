/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maax <maax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:48:25 by maax              #+#    #+#             */
/*   Updated: 2024/03/04 10:13:26 by maax             ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (argc < 5 || argc > 6)
		return (printf("Error, the program takes 5 or 6 arguments.\n"), 1);
	if (!ft_check_args(argv))
		return (printf("Error, arguments must be > 0 & can only contain digits.\n"), 1);
	init_data(argc, argv, &data);
	if (!init_forks(&data) || !init_philos(&data))
		return (EXIT_FAILURE);
	create_threads(&data);
	free(data.forks);
	free(data.philos);
	return (0);
}
