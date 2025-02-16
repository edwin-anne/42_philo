/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:33:37 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/02/14 20:26:35 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_global *global, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < global->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&global->dead_lock);
	pthread_mutex_destroy(&global->meal_lock);
	pthread_mutex_destroy(&global->write_lock);
}
