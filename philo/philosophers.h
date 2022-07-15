/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaby <afaby@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:27:27 by afaby             #+#    #+#             */
/*   Updated: 2022/07/15 14:47:19 by afaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

# define USAGE_MSG "Usage: ./philo nb_philo ttd tte tts [nb_philo_must_eat]" 
# define VALUE_ERR "Error: all values must be greater than 0."
# define MALLOC_ERROR "Error: malloc was not done correctly."
# define DIED 0
# define THINKING 1
# define EATING 2
# define SLEEPING 3
# define TAKE_FORK 4
# define HUNGRY 5
# define TIRED 6
# define HAVE_TO_THINK 7

typedef struct s_data t_data;

typedef struct s_philo
{
	pthread_t	id;
	int			index;
	int			status;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	int			fork;
	int			hands;
	t_data		*data;
}	t_philo;

struct s_data
{
	int			nb_philos;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	t_philo		*philos;
};

// ft_atoi.c
int		ft_atoi(const char *nptr);

// init.c
int		init_data(t_data *data, char *argv[]);

// message.c
void	choose_color(int philo);
void	choose_message(int type);
void	print_message(int timestamp, int philo, int type);

#endif
