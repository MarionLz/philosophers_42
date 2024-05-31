/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maax <maax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 09:54:20 by maax              #+#    #+#             */
/*   Updated: 2024/05/31 09:57:47 by maax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_content_arg(char *str)
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

int	check_args(char **argv)
{
	int i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0 || !check_content_arg(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("Error, the program takes 5 or 6 arguments.\n"), 1);
	if (!check_args(argv))
		return (printf("Error, arguments must be > 0 & can only contain digits.\n"), 1);
	return (0);
}