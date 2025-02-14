/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:46:59 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/02/14 11:41:06 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	if (!philo->eating && (get_current_time() - philo->last_meal >= philo->time_to_die))
	{
		*philo->dead = 1;
		pthread_mutex_unlock(philo->dead_lock);
		printf("%u %d died\n", get_current_time() - philo->start_time, philo->id);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*statut_philo(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philo->num_of_philos)
		{
			if (check_death(&philo[i]))
				return (NULL);
			i++;
		}
		ft_usleep(1);
	}
	return (NULL);
}

static int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	printf("%u %d has taken a fork\n", get_current_time() - philo->start_time, philo->id);
	pthread_mutex_lock(philo->r_fork);
	printf("%u %d has taken a fork\n", get_current_time() - philo->start_time, philo->id);
	
	philo->eating = 1;
	philo->last_meal = get_current_time();
	printf("%u %d is eating\n", get_current_time() - philo->start_time, philo->id);
	ft_usleep(philo->time_to_eat);
	philo->meals_eaten++;
	philo->eating = 0;
	
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

void	*history_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		pthread_mutex_lock(philo->dead_lock);
		if (*philo->dead)
		{
			pthread_mutex_unlock(philo->dead_lock);
			return (NULL);
		}
		pthread_mutex_unlock(philo->dead_lock);

		philo_eat(philo);
		printf("%u %d is sleeping\n", get_current_time() - philo->start_time, philo->id);
		ft_usleep(philo->time_to_sleep);
		printf("%u %d is thinking\n", get_current_time() - philo->start_time, philo->id);
	}
	return (NULL);
}