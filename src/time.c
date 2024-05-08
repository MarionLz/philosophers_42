/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maax <maax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:48:25 by maax              #+#    #+#             */
/*   Updated: 2024/05/01 15:19:21 by maax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	get_current_time(long int *current_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	*current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
}

long int	get_timestamp(t_philo *philo)
{
	long int timestamp;

	get_current_time(&philo->current_time);
	timestamp = philo->current_time - philo->data->start_time;
	return(timestamp);
}