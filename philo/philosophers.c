/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaby <afaby@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:44:02 by afaby             #+#    #+#             */
/*   Updated: 2022/07/15 14:48:26 by afaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_philo *philo, t_data *data, int i)
{
	philo->index = i;
	philo->time_to_die = data->time_to_die;
	philo->time_to_eat = data->time_to_eat;
	philo->time_to_sleep = data->time_to_sleep;
	philo->status = THINKING;
	philo->fork = 1;
	philo->hands = 0;
	philo->data = data;
}

void	 philo_eat(t_philo *data)
{
	if (data->status == THINKING)
	{
		while (data->hands != 2)
		{
			if (data->fork == 1)
			{
				data->fork = 0;
				data->hands++;
				print_message(2, data->index + 1, TAKE_FORK);
			}
			if (data->data->philos[(data->index + 1) % data->data->nb_philos].fork)
			{
				data->data->philos[(data->index + 1) % data->data->nb_philos].fork = 0;
				data->hands++;
				print_message(2, data->index + 1, TAKE_FORK);
			}
		}
		data->status = EATING;
		print_message(0, data->index + 1, EATING);
		usleep(data->time_to_eat);
		data->data->philos[(data->index + 1) % data->data->nb_philos].fork = 1;
		data->fork = 1;
		data->hands = 0;
		data->status = TIRED;
	}
}

void	philo_sleep(t_philo *data)
{
	if (data->status == TIRED)
	{
		data->status = SLEEPING;
		print_message(1, data->index + 1, SLEEPING);
		usleep(data->time_to_sleep);
		data->status = THINKING;
	}
}

void	*test(void *_data)
{
	t_philo	*data;

	data = (t_philo *) _data;
	while (1)
	{
		philo_eat(data);
		philo_sleep(data);
	}
	return (NULL);
}

void	launch_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		init_philo(&data->philos[i], data ,i);
		pthread_create(&data->philos[i].id, NULL, test, &data->philos[i]);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int		i;

	if (argc < 5 || argc > 6)
		return (printf("\033[0;31m%s\n", USAGE_MSG), 4);
	if (init_data(&data, argv) == 0)
		return (printf("\033[0;31m%s\n", VALUE_ERR), 5);
	data.philos = malloc(sizeof(t_philo) * data.nb_philos);
	if (!data.philos)
		return (printf("\033[0;31m%s\n", MALLOC_ERROR), 6);
	launch_philos(&data);
	i = 0;
	while (i < data.nb_philos)
		pthread_join(data.philos[i++].id, NULL);
	free(data.philos);
}
