/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:12:29 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/02/14 11:39:00 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	pthread_mutex_t	forks[200];
	t_philo			philo[200];
	t_global		global;

	if (!check(argc, argv))
		return (ft_error("Error : Argument Error\n"));
	if (!init_forks(forks, argv))
		return (ft_error("Error : Forks not initialized\n"));
	if (!create_mutex_global(&global, philo))
	{
		
		return (ft_error("Error : Global variable not initialized\n"));
	}
	init_philos(philo, &global, forks, argv);
	if (ft_atoi(argv[1]) == 1)
		execute_single_philo(philo);
	else
	{
		execute_multiple_philo(global, forks);
	}
	return (0);
}
