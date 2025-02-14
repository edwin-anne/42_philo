/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:20:11 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/02/14 09:20:19 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
    int num_of_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_times_to_eat;
}   t_philo;

/* utils.c */
int         ft_atoi(const char *str);
long int    ft_atol(const char *str);
int         str_is_digit(const char *str);
int         is_digit(int c);

/* error.c */
int         ft_error(char *str);

/* init.c */
int         check(int argc, char **argv);
void        insert(t_philo *philo, char **argv);

/* main.c */
int         main(int argc, char **argv);

/* monitor.c */
// Fonctions à venir pour la surveillance des philosophes

#endif
