/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maax <maax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 09:46:25 by maax              #+#    #+#             */
/*   Updated: 2024/05/31 09:51:04 by maax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_message(philo, "has taken a fork(R).\n", 1);
		pthread_mutex_lock(philo->l_fork);
		print_message(philo, "has taken a fork(L).\n", 1);
	}
	else
	{
		usleep(2000);
		pthread_mutex_lock(philo->l_fork);
		print_message(philo, "has taken a fork(L).\n", 1);
		pthread_mutex_lock(philo->r_fork);
		print_message(philo, "has taken a fork(R).\n", 1);
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}
