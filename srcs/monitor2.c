/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:34:49 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/02/17 13:01:05 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	unsigned int	current_time;

	pthread_mutex_lock(philo->dead_lock);
	current_time = get_current_time();
	if (*philo->dead)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	if (current_time - philo->last_meal >= philo->time_to_die)
	{
		*philo->dead = 1;
		pthread_mutex_unlock(philo->dead_lock);
		pthread_mutex_lock(philo->write_lock);
		printf("[%u] [%d] - died 💀\n",
			current_time - philo->start_time, philo->id);
		pthread_mutex_unlock(philo->write_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (print_status(philo, "has taken a fork 🍴"))
	{
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	pthread_mutex_lock(philo->r_fork);
	if (print_status(philo, "has taken a fork 🍴"))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	return (0);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	eat_meal(t_philo *philo)
{
	philo->eating = 1;
	philo->last_meal = get_current_time();
	if (print_status(philo, "is eating 🍔"))
	{
		release_forks(philo);
		return ;
	}
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	philo->eating = 0;
	release_forks(philo);
}

int	philo_eat(t_philo *philo)
{
	if (check_death(philo))
		return (1);
	if (take_forks(philo))
		return (1);
	eat_meal(philo);
	return (0);
}
