/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malauzie <malauzie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 09:54:20 by maax              #+#    #+#             */
/*   Updated: 2024/06/04 12:03:01 by malauzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

bool	is_input_valid(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (printf("Error, the program takes 5 or 6 arguments.\n"), false);
	if (ft_atoi(argv[i]) <= 0)
		return (printf("Error, number of philosophers must be > 0.\n"), false);
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 0)
			return (printf("Error, args must be >= 0\n"), false);
		if (!is_digit(argv[i]))
			return (printf("Error, args can only contain digits.\n"), false);
		i++;
	}
	return (true);
}
