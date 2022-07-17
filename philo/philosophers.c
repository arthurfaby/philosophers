/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaby <afaby@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 09:24:41 by afaby             #+#    #+#             */
/*   Updated: 2022/07/17 13:40:57 by afaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	long long int	res;
	int				neg;

	res = 0;
	neg = 1;
	while (((*nptr >= 9 && *nptr <= 13) || *nptr == ' ') && *nptr)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			neg = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr - '0');
		nptr++;
	}
	return ((int)neg * res);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i] = malloc(sizeof(t_philo));
		if (!data->philos[i])
			return ;
		data->philos[i]->index = i;
		data->philos[i]->data = data;
		pthread_mutex_init(&data->philos[i]->fork, NULL);
		data->philos[i]->last_meal = data->start;
		i++;
	}
}

int	init_data(t_data *data, char *argv[])
{
	struct timeval	date;

	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]) * 1000;
	data->time_to_eat = ft_atoi(argv[3]) * 1000;
	data->time_to_sleep = ft_atoi(argv[4]) * 1000;
	data->finished = 0;
	gettimeofday(&date, NULL);
	data->start = date.tv_sec * 1000 + date.tv_usec / 1000;
	if (data->nb_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (0);
	pthread_mutex_init(&data->message, NULL);
	data->philos = malloc(sizeof(t_philo *) * data->nb_philos);
	if (!data->philos)
		return (0);
	init_philos(data);
	return (1);
}

void	take_forks(t_philo *philo)
{
	int	neighbour_index;
	int	self_index;

	self_index = philo->index;
	neighbour_index = (self_index + 1) % philo->data->nb_philos;
	pthread_mutex_lock(&philo->data->philos[self_index]->fork);
	if (philo->data->finished)
		return ;
	print_message(philo->data, philo->index + 1, TAKE_FORK);
	pthread_mutex_lock(&philo->data->philos[neighbour_index]->fork);
	if (philo->data->finished)
		return ;
	print_message(philo->data, philo->index + 1, TAKE_FORK);
}

void	put_forks(t_philo *philo)
{
	int	neighbour_index;
	int	self_index;

	self_index = philo->index;
	neighbour_index = (self_index + 1) % philo->data->nb_philos;
	pthread_mutex_unlock(&philo->data->philos[neighbour_index]->fork);
	pthread_mutex_unlock(&philo->data->philos[self_index]->fork);
}

void	eat(t_philo *philo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (philo->data->finished)
		return ;
	print_message(philo->data, philo->index + 1, EATING);
	philo->last_meal = now.tv_sec * 1000 + now.tv_usec / 1000;
	usleep(philo->data->time_to_eat);
}

void	philo_sleep(t_philo *philo)
{	
	if (philo->data->finished)
		return ;
	print_message(philo->data, philo->index + 1, SLEEPING);
	usleep(philo->data->time_to_sleep);
	if (philo->data->finished)
		return ;
	print_message(philo->data, philo->index + 1, THINKING);
}

void	*start_routine(void *_philo)
{
	t_philo	*philo;

	philo = (t_philo *)_philo;
	while (!philo->data->finished)
	{
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	*fchecker(void *_data)
{
	t_data			*data;
	int				i;
	struct timeval	now;
	long long		m_now;

	data = (t_data *)_data;
	while (1)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			gettimeofday(&now, NULL);
			m_now = now.tv_sec * 1000 + now.tv_usec / 1000;
			if (m_now - data->philos[i]->last_meal > (data->time_to_die / 1000))
			{
				print_message(data, data->philos[i]->index + 1, DIED);
				data->finished = 1;
				return (NULL);
			}
			i++;
		}		
	}
	return (NULL);
}

void	launch_philos(t_data *data, pthread_t *checker)
{
	int			i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_create(&data->philos[i]->id, NULL, start_routine, data->philos[i]);
		usleep(500);
		i++;
	}
	pthread_create(checker, NULL, fchecker, data);
	pthread_join(*checker, NULL);
}

void	wait_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philos[i]->id, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data		data;
	pthread_t	checker;
	
	if (!init_data(&data, argv))
		return (1);
	launch_philos(&data, &checker);
	//wait_philos(&data);
	return (0);
	(void)argc;	
}
