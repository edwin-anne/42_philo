/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:31:10 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/02/14 10:32:42 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(int milliseconds)
{
	unsigned int	start;

	start = get_current_time();
	while ((get_current_time() - start) < (unsigned int)milliseconds)
		usleep(500);
	return (0);
}