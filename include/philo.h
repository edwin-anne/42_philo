/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Edwin ANNE <eanne@student.42lehavre.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:20:11 by Edwin ANNE        #+#    #+#             */
/*   Updated: 2025/02/14 11:38:42 by Edwin ANNE       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	unsigned int	last_meal;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;
typedef struct	s_global
{
	int				dead;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}	t_global;


/* utils.c */
int         	ft_atoi(const char *str);
int         	is_number(char *str);
long        	ft_atol(const char *str);
unsigned int	get_current_time(void);

/* utils2.c */
int				ft_usleep(int milliseconds);

/* error.c */
int         	ft_error(char *str);

/* init.c */
int         	check(int argc, char **argv);
int				init_forks(pthread_mutex_t *forks, char **argv);
void			insert_global(t_philo *philo, char **argv);
void			init_philos(t_philo *philos, t_global *program, pthread_mutex_t *forks,
					char **argv);
int				create_mutex_global(t_global *global, t_philo *philos);

/* main.c */
int         	main(int argc, char **argv);

/* execute.c */
void			execute_single_philo(t_philo *philo);
int				execute_multiple_philo(t_global global, pthread_mutex_t *forks);

/* clean.c */
void		clean(t_global *global, pthread_mutex_t *forks);

/* monitor.c */
void		*statut_philo(void *arg);
void		*history_philo(void *arg);

#endif
