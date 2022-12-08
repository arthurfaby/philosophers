/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaby <afaby@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 09:42:20 by afaby             #+#    #+#             */
/*   Updated: 2022/09/12 16:16:41 by afaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define THINKING "is thinking\n"
# define EATING "is eating\n"
# define SLEEPING "is sleeping\n"
# define TAKE_FORK "has taken a fork\n"

typedef struct s_data	t_data;

typedef struct s_philo
{
	long long		last_meal;
	int				n_meals;
	int				index;
	pthread_t		id;
	pthread_mutex_t	fork;
	t_data			*data;
}	t_philo;

struct s_data
{
	int				finished;
	long long		start;
	int				nb_philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				max_meal;
	pthread_mutex_t	m_message;
	pthread_mutex_t	m_meals;
	pthread_mutex_t	m_finished;
	t_philo			**philos;
};

// ft_atoi.c
int		ft_atoi(const char *nptr);

// message.c
void	print_message(t_data *data, int philo, char *msg);
void	choose_message(int type);
void	choose_color(int philo);

// init.c
void	init_philos(t_data *data);
int		init_data(t_data *data, char *argv[], int argc);

// actions.c
int		take_forks(t_philo *philo);
void	put_forks(t_philo *philo);
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);

// routines.c
void	*start_routine(void *_philo);
void	*checker_routine(void *_data);
void	launch_philos(t_data *data, pthread_t *checker);

// free.c
void	free_philos(t_philo *philo);
void	free_data(t_data *data);

// time.c
void	my_mssleep(int ms);

#endif
