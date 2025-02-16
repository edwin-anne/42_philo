/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:31:10 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/02/14 10:32:42 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(int milliseconds)
{
	unsigned int	start;
	unsigned int	current;

	start = get_current_time();
	while (1)
	{
		current = get_current_time();
		if (current - start >= (unsigned int)milliseconds)
			break ;
		usleep(100);
	}
	return (0);
}

int	print_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->write_lock);
	pthread_mutex_lock(philo->dead_lock);
	if (!(*philo->dead))
	{
		printf("[%u] [%d] - %s\n", get_current_time() - philo->start_time,
			philo->id, str);
		pthread_mutex_unlock(philo->dead_lock);
		pthread_mutex_unlock(philo->write_lock);
		return (0);
	}
	pthread_mutex_unlock(philo->dead_lock);
	pthread_mutex_unlock(philo->write_lock);
	return (1);
}

void    *ft_memset(void *s, int c, size_t n)
{
        unsigned char   *p;

        p = s;
        while (n > 0)
        {
                *p = c;
                p++;
                n--;
        }
        return (s);
}