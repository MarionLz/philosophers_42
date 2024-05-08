/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maax <maax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:59:21 by maax              #+#    #+#             */
/*   Updated: 2024/05/08 14:11:04 by maax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	digit;

	sign = 1;
	digit = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == 43 || *nptr == 45)
	{
		if (*nptr == 45)
			sign *= -1;
		nptr++;
	}
	while (*nptr >= 48 && *nptr <= 57)
	{
		digit = (digit * 10) + *nptr - 48;
		nptr++;
	}
	return (digit * sign);
}

void	print_message(t_philo *philo, char *message, int flag)
{
	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->dead_philo)
	{
		if (flag == 1)
			printf("%ld %d %s", get_timestamp(philo), philo->id, message);
		if (flag == 2)
			printf("%ld %d %s %d/%d meals.\n",  get_timestamp(philo), philo->id, message, philo->nb_meals, philo->data->nb_each_philo_must_eat);
		if (flag == 3)
			printf("%ld %s", get_timestamp(philo), message);
	}
	pthread_mutex_unlock(&philo->data->print);
}
