/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaby <afaby@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:38:59 by afaby             #+#    #+#             */
/*   Updated: 2022/07/16 12:04:14 by afaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	choose_color(int philo)
{
	if (philo % 6 == 0)
		printf("\033[0;32m");
	else if (philo % 6 == 1)
		printf("\033[0;33m");
	else if (philo % 6 == 2)
		printf("\033[0;34m");
	else if (philo % 6 == 3)
		printf("\033[0;35m");
	else if (philo % 6 == 4)
		printf("\033[0;36m");
	else if (philo % 6 == 5)
		printf("\033[0;37m");
}

void	choose_message(int type)
{
	if (type == TAKE_FORK)
		printf("has taken a fork.");
	else if (type == EATING)
		printf("is eating.");
	else if (type == SLEEPING)
		printf("is sleeping.");
	else if (type == THINKING)
		printf("is thinking.");
}

void	print_message(t_data *data, int philo, int type)
{
	struct timeval	now;
	long			m_now;
	long			timestamp;

	gettimeofday(&now, NULL);
	m_now = now.tv_sec * 1000 + now.tv_usec / 1000;
	timestamp = m_now - data->start;
	pthread_mutex_lock(&data->message);
	if (type == DIED)
	{
		printf("\033[0;31m%ld %d died.\n", timestamp, philo);
		return ;
	}
	choose_color(philo);
	usleep(50);
	printf("%ld %d ", timestamp, philo);
	choose_message(type);
	printf("\n\033[0m");
	pthread_mutex_unlock(&data->message);
}
