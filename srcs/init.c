/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:57:30 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/02/14 09:23:41 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

int	check(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (0);
	if ((ft_atol(argv[1]) > 200 || ft_atol(argv[1]) < 1)
		|| (ft_atol(argv[2]) > INT_MAX || ft_atol(argv[2]) < 1)
		|| (ft_atol(argv[3]) > INT_MAX || ft_atol(argv[3]) < 1)
		|| (ft_atol(argv[4]) > INT_MAX || ft_atol(argv[4]) < 1))
		return (0);
	if (argc == 6)
	{
		if (ft_atol(argv[5]) > INT_MAX || ft_atol(argv[5]) < 1)
			return (0);
	}
	return (1);
}

// void	insert(t_philo *philo, char **argv)
// {
// 	philo->time_to_die = ft_atoi(argv[2]);
// 	philo->time_to_eat = ft_atoi(argv[3]);
// 	philo->time_to_sleep = ft_atoi(argv[4]);
// 	philo->num_of_philos = ft_atoi(argv[1]);
// 	if (argv[5] != NULL)
// 		philo->num_times_to_eat = ft_atoi(argv[5]);
// 	else
// 		philo->num_times_to_eat = -1;
// }
