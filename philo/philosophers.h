/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaby <afaby@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 09:42:20 by afaby             #+#    #+#             */
/*   Updated: 2022/07/16 14:14:23 by afaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>
# include <unistd.h>

# define DIED 0
# define THINKING 1
# define EATING 2
# define SLEEPING 3
# define TAKE_FORK 4

typedef struct s_data t_data;

typedef struct s_philo
{
	long long		last_meal;
	int				index;
	pthread_t		id;
	pthread_mutex_t	fork;
	t_data			*data;
}	t_philo;

struct s_data
{
	int				finished;
	long long 		start;
	int				nb_philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	pthread_mutex_t	message;
	t_philo			**philos;
};

void	print_message(t_data *data, int philo, int type);
void	choose_message(int type);
void	choose_color(int philo);

#endif
