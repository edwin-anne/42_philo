/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:46:59 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/02/16 10:17:52 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_all_ate(t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	printf("The philosophers all ate %d times make ✅\n",
		philo->num_times_to_eat);
	pthread_mutex_unlock(philo->write_lock);
	pthread_mutex_lock(philo->dead_lock);
	*philo->dead = 1;
	pthread_mutex_unlock(philo->dead_lock);
	return (1);
}

int	check_meals(t_philo *philo)
{
	int	i;
	int	all_ate_enough;

	if (philo->num_times_to_eat == -1)
		return (0);
	i = 0;
	all_ate_enough = 1;
	pthread_mutex_lock(philo->meal_lock);
	while (i < philo->num_of_philos)
	{
		if (philo[i].meals_eaten < philo->num_times_to_eat)
		{
			all_ate_enough = 0;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(philo->meal_lock);
	if (all_ate_enough)
		return (handle_all_ate(philo));
	return (0);
}

void	*statut_philo(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	ft_usleep(10);
	while (1)
	{
		i = 0;
		while (i < philo->num_of_philos)
		{
			if (check_death(&philo[i]))
				return (NULL);
			if (check_meals(&philo[i]))
				return (NULL);
			i++;
		}
		usleep(100);
	}
	return (NULL);
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
		if (philo_eat(philo))
			return (NULL);
		if (print_status(philo, "is sleeping 🌙"))
			return (NULL);
		ft_usleep(philo->time_to_sleep);
		if (print_status(philo, "is thinking 🤔"))
			return (NULL);
	}
	return (NULL);
}
