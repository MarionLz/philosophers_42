/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maax <maax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 09:46:25 by maax              #+#    #+#             */
/*   Updated: 2024/06/14 11:44:02 by maax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		usleep(3000);
		pthread_mutex_lock(philo->l_fork);
	}
	else
		pthread_mutex_lock(philo->r_fork);
	if (!stop_activity(philo))
		print_message(philo, "has taken a fork. 🍴\n", 1);
	if (philo->id % 2 == 0)
	{
		usleep(3000);
		pthread_mutex_lock(philo->r_fork);
	}
	else
		pthread_mutex_lock(philo->l_fork);
	if (!stop_activity(philo))
		print_message(philo, "has taken a fork. 🍴\n", 1);
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}
