/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malauzie <malauzie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:49:26 by maax              #+#    #+#             */
/*   Updated: 2024/06/04 12:09:36 by malauzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		thread_philo;
	int				id;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	long int		time_of_death;
	long int		current_time;
	int				nb_meals;
	bool			is_full;
	pthread_mutex_t	meals;
}	t_philo;

typedef struct s_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_each_philo_must_eat;
	int				stop_simulation;
	pthread_mutex_t	dead;
	pthread_t		thread_monitor;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	long int		start_time;
	pthread_mutex_t	print;
	int				all_full;
	pthread_mutex_t	full;
}	t_data;

/* MAIN */
void		free_all(t_data *data);
void		lonesome_cowboy(t_data *data);
int			main(int argc, char **argv);

/* CHECK INPUT */
bool		is_input_valid(int argc, char **argv);
bool		is_digit(char *str);

/* INIT */
void		init_data(int argc, char **argv, t_data *data);
int			init_philos(t_data *data);
int			init_forks(t_data *data);

/* THREADS */
void		create_threads(t_data *data);
void		wait_threads(t_data *data);

/* PHILOS ROUTINE */
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);
void		*philos_routine(void *struct_philo);

/* FORKS */
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);

/* MONITOR */
void		check_philo_life(t_philo *philo);
void		check_nb_meals(t_philo *philo);
void		monitor(t_data *data);

/* TIME */
void		get_current_time(long int *current_time);
long int	get_timestamp(t_philo *philo);
void		init_time_of_death(t_philo *philo);

/* UTILS */
int			ft_atoi(const char *nptr);
void		print_message(t_philo *philo, char *message, int flag);

#endif
