/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:28:43 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/02/17 13:03:35 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	execute_single_philo(t_philo *philo)
{
	printf("[%u] [%d] - has taken a fork 🍴\n",
		get_current_time() - philo->start_time,
		philo->id);
	ft_usleep(philo->time_to_die);
	printf("[%u] [%d] - died 💀\n",
		get_current_time() - philo->start_time, philo->id);
}

int	execute_multiple_philo(t_global global, pthread_mutex_t *forks)
{
	int			i;
	t_philo		*philos;
	pthread_t	monitor;

	philos = global.philos;
	i = 0;
	if (pthread_create(&monitor, NULL, &statut_philo, &philos[0]) != 0)
		return (1);
	while (i < philos[0].num_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL,
				&history_philo, &philos[i]) != 0)
			return (1);
		i++;
	}
	pthread_join(monitor, NULL);
	i = 0;
	while (i < philos[0].num_of_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	clean(&global, forks);
	return (0);
}
