/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:57:30 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/02/14 10:26:17 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

int	check(int argc, char **argv)
{
	int		i;
	long	num;

	i = 1;
	if (argc != 5 && argc != 6)
		return (0);
	while (i < argc)
	{
		if (!is_number(argv[i]))
			return (0);
		num = ft_atol(argv[i]);
		if (num > INT_MAX || num < 1 || (i == 1 && num > 200))
			return (0);
		i++;
	}
	return (1);
}

int	init_forks(pthread_mutex_t *forks, char **argv)
{
	int	i;
	int	philo_number;

	i = 0;
	philo_number = atoi(argv[1]);
	while (i < philo_number)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	insert_global(t_philo *philo, char **argv)
{
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->num_of_philos = ft_atoi(argv[1]);
	if (argv[5])
		philo->num_times_to_eat = ft_atoi(argv[5]);
	else
		philo->num_times_to_eat = -1;
}

void	init_philos(t_philo *philos, t_global *program, pthread_mutex_t *forks,
	char **argv)
{
	int				i;
	unsigned int	start_time;

	start_time = get_current_time();
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		insert_global(&philos[i], argv);
		philos[i].start_time = start_time;
		philos[i].last_meal = start_time;
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead = &program->dead;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].num_of_philos - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
}

int	create_mutex_global(t_global *global, t_philo *philos)
{
	global->dead = 0;
	global->philos = philos;
	if (pthread_mutex_init(&global->dead_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&global->meal_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&global->write_lock, NULL) != 0)
		return (0);
	return (1);
}